# Lab 21: RS485 Multi-drop & Addressing (หลาย Node บนบัสเดียว)

## Overview (ภาพรวม)
จุดเด่นที่สุดของ RS485 คือรองรับอุปกรณ์ได้ถึง **32 ตัว (หรือมากกว่าด้วย repeater)** บนสายคู่เดียวกัน (Multi-drop) แต่เมื่อมีหลายตัวบนบัสเดียว จำเป็นต้องมี **ที่อยู่ (Address / Slave ID)** เพื่อระบุว่า Master กำลังคุยกับใคร อุปกรณ์ที่ไม่ใช่ปลายทางต้อง "เงียบ"

แลปนี้จำลองสถานี Node หลายตัว (เช่น Node 1, Node 2) ต่อบนบัสเดียวกัน Master จะ **Poll (วนถาม)** ทีละ Address และเฉพาะ Slave ที่ตรง Address เท่านั้นที่ตอบกลับ นี่คือหลักการเดียวกับที่ Modbus และ SCADA ใช้จริง

## Hardware Wiring (การต่อวงจร)
ต่อ MAX485 ทุกบอร์ดเหมือน Lab 19–07 และ **เชื่อมสาย A↔A↔A, B↔B↔B, GND ร่วม** ทุกตัวขนานกันบนบัสเดียว

```
[Master] ──┬── A ──┬── A ──┐
           │       │       │
        [Node1] [Node2]  ... (ขนานกันบนบัส)
```

> แต่ละ Slave ตั้ง `MY_ADDRESS` ในโค้ดให้ไม่ซ้ำกัน (เช่น Node1 = 1, Node2 = 2) | ปลายบัสควรมี Termination 120Ω

## รูปแบบ Frame คำสั่ง (Protocol)
ใช้รูปแบบข้อความง่ายๆ: `<address>:<command>`
- ตัวอย่าง: `1:READ` = ถาม Node 1 ให้ส่งค่า, `2:READ` = ถาม Node 2
- Slave ตอบกลับเป็น `<address>:<value>` เพื่อให้ Master ยืนยันว่ามาจากใคร

## Code – Master (Poll ทีละ Node)
```cpp
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;
const int NODE_LIST[] = {1, 2};   // รายชื่อ Node ที่จะวนถาม
const int NODE_COUNT = 2;

void sendCommand(String cmd) {
  digitalWrite(DE_RE, HIGH); delay(2);
  rs485.println(cmd);
  rs485.flush();
  digitalWrite(DE_RE, LOW);
}

String readReply(unsigned long timeout = 400) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (rs485.available()) return rs485.readStringUntil('\n');
  }
  return "TIMEOUT";
}

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- MASTER (Multi-drop Poll) ---");
}

void loop() {
  for (int i = 0; i < NODE_COUNT; i++) {
    int addr = NODE_LIST[i];
    sendCommand(String(addr) + ":READ");

    String reply = readReply();
    reply.trim();
    Serial.print("Node "); Serial.print(addr);
    Serial.print(" -> "); Serial.println(reply);

    delay(500);   // เว้นจังหวะก่อนถาม Node ถัดไป
  }
  Serial.println("------------------");
  delay(1000);
}
```

## Code – Slave (ตอบเฉพาะ Address ของตัวเอง)
```cpp
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;
const int sensorPin = A0;

// >>> ตั้งให้ไม่ซ้ำกันในแต่ละบอร์ด <<<
const int MY_ADDRESS = 1;   // Node1 = 1, Node2 = 2 ...

void sendReply(String msg) {
  digitalWrite(DE_RE, HIGH); delay(2);
  rs485.println(msg);
  rs485.flush();
  digitalWrite(DE_RE, LOW);
}

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.print("--- SLAVE Node #"); Serial.print(MY_ADDRESS); Serial.println(" ---");
}

void loop() {
  if (rs485.available()) {
    String frame = rs485.readStringUntil('\n');
    frame.trim();

    int sep = frame.indexOf(':');
    if (sep < 0) return;

    int targetAddr = frame.substring(0, sep).toInt();
    String cmd = frame.substring(sep + 1);

    // ตอบเฉพาะเมื่อ Address ตรงกับเรา
    if (targetAddr == MY_ADDRESS && cmd == "READ") {
      int val = analogRead(sensorPin);
      sendReply(String(MY_ADDRESS) + ":" + String(val));
    }
    // ถ้าไม่ใช่ Address เรา -> เงียบ (ไม่ตอบ)
  }
}
```

## คำอธิบายโค้ด
- **Addressing** ทำให้หลายอุปกรณ์อยู่ร่วมบัสเดียวได้ Master แยกแยะด้วย Slave ID
- Master **Poll แบบวนรอบ** (Round-robin) ทีละ Node ป้องกันการชนกัน
- การเว้นจังหวะ (`delay` ระหว่าง Node) สำคัญ เพื่อให้ Slave ตัวก่อนปล่อยบัสก่อนถามตัวถัดไป
- หากต่อ Node เพิ่ม แค่เพิ่มเลขใน `NODE_LIST` และตั้ง `MY_ADDRESS` ใหม่ — ขยายระบบได้ง่าย

## 🧪 โจทย์ท้าย Lab
1. เพิ่ม Node ที่ 3 (Address 3) เข้าระบบ โดยแก้โค้ดให้น้อยที่สุด
2. ทำให้ Master ตรวจจับ Node ที่ "หาย" (ตอบ TIMEOUT) แล้วพิมพ์แจ้งเตือนว่า Node ใดออฟไลน์
3. คำถาม: ถ้า 2 Slave ตั้ง Address ซ้ำกันจะเกิดอะไรขึ้นบนบัส? และเหตุใด Modbus จึงกำหนดให้ Address ต้องไม่ซ้ำ?

