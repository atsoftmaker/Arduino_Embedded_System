# Lab 07: RS485 แบบ Master / Slave Command

## Overview (ภาพรวม)
ในระบบอุตสาหกรรมจริง การสื่อสารบนบัส RS485 จะเป็นแบบ **Request–Response**: อุปกรณ์ตัวหนึ่งเป็น **Master** (ผู้ถาม) และอีกตัวเป็น **Slave** (ผู้ตอบ) Master จะส่ง "คำสั่ง" ไป แล้ว Slave ตอบกลับเฉพาะเมื่อถูกถาม วิธีนี้ป้องกันการชนกันของข้อมูล (Collision) บนบัส

แลปนี้ต่อยอดจาก Lab 06 โดยสร้าง **Protocol คำสั่งอย่างง่าย**:
- Master ส่ง `READ` → Slave ตอบค่าเซนเซอร์ (จำลองด้วย VR)
- Master ส่ง `LED:ON` / `LED:OFF` → Slave ควบคุม LED ตามคำสั่ง แล้วตอบ `ACK`

นี่คือพื้นฐานก่อนเข้าสู่ Modbus (Lab 09) ซึ่งเป็น Protocol Master/Slave มาตรฐานสากล

## Hardware Wiring (การต่อวงจร)
ใช้การต่อ MAX485 เหมือน Lab 06 ทุกประการ (DI=D3, RO=D2, DE+RE=D4, A↔A, B↔B, GND ร่วม)

**เพิ่มฝั่ง Slave:**

| อุปกรณ์ | Arduino UNO (Slave) |
| :--- | :--- |
| VR ขากลาง (จำลองเซนเซอร์) | **A0** |
| LED ผ่าน R 220Ω | **D7** |

## Code – Master
```cpp
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;

void sendCommand(String cmd) {
  digitalWrite(DE_RE, HIGH); delay(2);   // โหมดส่ง
  rs485.println(cmd);
  rs485.flush();
  digitalWrite(DE_RE, LOW);              // กลับมาโหมดรับ
}

String readReply(unsigned long timeout = 500) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (rs485.available()) {
      return rs485.readStringUntil('\n');
    }
  }
  return "TIMEOUT";
}

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- MASTER ---");
}

void loop() {
  // 1) ขอค่าเซนเซอร์
  sendCommand("READ");
  Serial.print("Sensor = "); Serial.println(readReply());
  delay(1000);

  // 2) สั่งเปิดไฟ
  sendCommand("LED:ON");
  Serial.print("Reply  = "); Serial.println(readReply());
  delay(1000);

  // 3) สั่งปิดไฟ
  sendCommand("LED:OFF");
  Serial.print("Reply  = "); Serial.println(readReply());
  delay(1000);
}
```

## Code – Slave
```cpp
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;
const int ledPin = 7;
const int sensorPin = A0;

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
  pinMode(ledPin, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- SLAVE ---");
}

void loop() {
  if (rs485.available()) {
    String cmd = rs485.readStringUntil('\n');
    cmd.trim();
    Serial.print("รับคำสั่ง: "); Serial.println(cmd);

    if (cmd == "READ") {
      int val = analogRead(sensorPin);
      sendReply(String(val));
    } else if (cmd == "LED:ON") {
      digitalWrite(ledPin, HIGH);
      sendReply("ACK:LED_ON");
    } else if (cmd == "LED:OFF") {
      digitalWrite(ledPin, LOW);
      sendReply("ACK:LED_OFF");
    } else {
      sendReply("ERR:UNKNOWN");
    }
  }
}
```

## คำอธิบายโค้ด
- **Request–Response**: Slave จะ "เงียบ" จนกว่าจะถูกถาม ป้องกันการชนกันบนบัส
- Master มี `readReply()` พร้อม **Timeout** — ถ้า Slave ไม่ตอบใน 500ms จะคืน `TIMEOUT` (สำคัญมากในงานจริง เพราะอุปกรณ์อาจหลุด)
- Protocol นี้ใช้ข้อความ (ASCII) อ่านง่ายตอนเรียน แต่ Modbus จะใช้ binary frame ที่กระชับและมี CRC ตรวจสอบ (Lab 09)

## 🧪 โจทย์ท้าย Lab
1. เพิ่มคำสั่ง `STATUS` ให้ Slave ตอบทั้งค่าเซนเซอร์และสถานะ LED ในข้อความเดียว
2. ทำให้ Master นับจำนวนครั้งที่ได้ `TIMEOUT` และแจ้งเตือนเมื่อเกิน 3 ครั้งติด
3. คำถาม: ทำไมระบบ Master/Slave จึงเหมาะกับ RS485 มากกว่าการให้ทุกตัวส่งข้อมูลอิสระ?
