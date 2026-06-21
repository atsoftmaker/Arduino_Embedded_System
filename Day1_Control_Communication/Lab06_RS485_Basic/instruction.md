# Lab 06: พื้นฐานการสื่อสาร RS485

## Overview (ภาพรวม)
**RS485** เป็นมาตรฐานการสื่อสารแบบ Serial ที่ใช้กันแพร่หลายที่สุดในงานอุตสาหกรรม เพราะส่งข้อมูลได้ไกลถึง **1,200 เมตร** ทนสัญญาณรบกวนได้ดี (Differential Signal บนสาย A/B) และรองรับการต่ออุปกรณ์หลายตัวบนสายเดียว (Multi-drop)

ต่างจาก Serial ปกติ (UART/TTL) ตรงที่ RS485 ส่งสัญญาณเป็น **ผลต่างแรงดันระหว่างสาย A และ B** ทำให้ภูมิคุ้มกันสัญญาณรบกวนสูง เหมาะกับสภาพแวดล้อมโรงงานที่มีมอเตอร์และไฟกำลัง

ในแลปนี้เราจะต่อบอร์ด **2 ตัว** (Board A ส่ง, Board B รับ) ผ่านโมดูล **MAX485** เพื่อส่งข้อความพื้นฐาน และเข้าใจการควบคุมทิศทาง (Half-Duplex) ด้วยขา DE/RE

## Hardware Wiring (การต่อวงจร)

โมดูล MAX485 มี 4 ขาฝั่งไมโครคอนโทรลเลอร์: VCC, GND, DI (Driver In), RO (Receiver Out), DE (Driver Enable), RE (Receiver Enable)

**ต่อ MAX485 กับ Arduino แต่ละบอร์ดเหมือนกัน:**

| MAX485 | Arduino UNO |
| :--- | :--- |
| **VCC** | 5V |
| **GND** | GND |
| **DI** | **D3** (TX) |
| **RO** | **D2** (RX) |
| **DE + RE** (ต่อร่วมกัน) | **D4** (ควบคุมทิศทาง) |

**ต่อระหว่างโมดูล MAX485 สองตัว (สาย Bus):**

| Board A (MAX485) | Board B (MAX485) |
| :--- | :--- |
| **A** | **A** |
| **B** | **B** |
| **GND** | **GND** (Common Ground สำคัญมาก) |

> ⚠️ ใช้ `SoftwareSerial` ที่ขา D2/D3 เพื่อเก็บ Serial หลัก (D0/D1) ไว้ดู Monitor บนคอม | ต่อ A↔A, B↔B (ห้ามไขว้) | ปลายสายทั้งสองด้านของ Bus ยาวๆ ควรมี Termination Resistor 120Ω

## Code – ฝั่งส่ง (Sender / Board A)
```cpp
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3); // RX=D2, TX=D3
const int DE_RE = 4;

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);  // เริ่มที่โหมดรับ
  Serial.println("--- Board A: RS485 Sender ---");
}

void loop() {
  // สลับเป็นโหมดส่ง (Transmit)
  digitalWrite(DE_RE, HIGH);
  delay(2);
  rs485.println("HELLO from Board A");
  rs485.flush();             // รอให้ส่งครบทุก byte
  // กลับเป็นโหมดรับ
  digitalWrite(DE_RE, LOW);

  Serial.println("ส่ง: HELLO from Board A");
  delay(1000);
}
```

## Code – ฝั่งรับ (Receiver / Board B)
```cpp
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3); // RX=D2, TX=D3
const int DE_RE = 4;

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);  // คงโหมดรับไว้ตลอด
  Serial.println("--- Board B: RS485 Receiver ---");
}

void loop() {
  if (rs485.available()) {
    String msg = rs485.readStringUntil('\n');
    Serial.print("รับได้: ");
    Serial.println(msg);
  }
}
```

## คำอธิบายโค้ด
- **ขา DE/RE** คือหัวใจของ RS485 แบบ Half-Duplex: ต่อร่วมกันแล้วคุมด้วยขาเดียว
  - `HIGH` = โหมดส่ง (Driver Enable)
  - `LOW` = โหมดรับ (Receiver Enable)
- ต้องสลับเป็นโหมดส่ง **ก่อน** ส่งข้อมูล และ `flush()` ให้ส่งครบ **ก่อน** สลับกลับมารับ มิฉะนั้นข้อมูลจะขาด
- `SoftwareSerial` จำลองพอร์ต Serial ที่ขาอื่น เพื่อเก็บ Hardware Serial (D0/D1) ไว้ debug

## 🧪 โจทย์ท้าย Lab
1. แก้ Board A ให้ส่งค่าตัวนับ (counter) ที่เพิ่มขึ้นทุกครั้ง แล้วให้ Board B แสดงค่า
2. ลองถอดสาย GND ร่วมออก แล้วสังเกตว่าการสื่อสารยังทำงานหรือไม่ (เรียนรู้ความสำคัญของ Common Ground)
3. คำถาม: RS485 ต่างจาก RS232 อย่างไร? ทำไม RS485 ถึงส่งได้ไกลและทนรบกวนกว่า?
