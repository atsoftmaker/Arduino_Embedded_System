# Lab 13: ESP32 Gateway ดึงข้อมูลจาก Node ผ่าน RS485 (Modbus Master)

## Overview (ภาพรวม)
นี่คือการรวมร่างของทั้งหลักสูตร: ESP32 ทำหน้าที่เป็น **Gateway** — สะพานเชื่อมระหว่างโลก 2 ใบ
- **ฝั่งล่าง (Field):** พูด Modbus RTU ผ่าน RS485 ไปอ่านข้อมูลจาก Node (Arduino UNO ที่เป็น Modbus Slave จาก Lab 09)
- **ฝั่งบน (Enterprise):** เชื่อม Wi-Fi องค์กร (จาก Lab 11–12) เตรียมส่งข้อมูลขึ้น OPS Server (Lab 14)

ในแลปนี้ ESP32 เป็น **Modbus Master** วน Poll อ่าน Holding Register จาก UNO Node เปลี่ยนบอร์ดราคาถูกให้กลายเป็นตัวรวบรวมข้อมูล (Data Concentrator) แบบที่ใช้ในโรงงานจริง

## ⚠️ เรื่องแรงดันไฟ (สำคัญมาก)
ESP32 = 3.3V, UNO = 5V — **ห้ามต่อ TX/RX ข้ามบอร์ดตรงๆ** แต่ในแลปนี้เราต่อผ่านโมดูล **MAX485 ของแต่ละฝั่ง** ซึ่งสื่อสารกันบนบัส RS485 (สาย A/B) จึงปลอดภัย เพราะระดับลอจิกถูกแยกด้วยโมดูล

## ไลบรารีที่ต้องติดตั้ง
- **ModbusMaster** (โดย Doc Walker) — ติดตั้งผ่าน Library Manager

## Hardware Wiring (การต่อวงจร)

**ฝั่ง ESP32 + MAX485:**

| MAX485 | ESP32 |
| :--- | :--- |
| DI | **GPIO 17 (TX2)** |
| RO | **GPIO 16 (RX2)** |
| DE + RE | **GPIO 4** |
| VCC | **3.3V หรือ 5V** (ดูสเปกโมดูล*) |
| GND | GND |

> *MAX485 ส่วนใหญ่ต้องใช้ VCC = 5V ให้ขับสายได้ไกล แต่ขาสัญญาณ DI/RO ที่ต่อกับ ESP32 ควรเป็น 3.3V — โมดูลรุ่นที่จ่าย 3.3V ได้จะปลอดภัยสุด หากใช้ 5V ควรมีตัวต้านทานแบ่งแรงดันที่ขา RO

**บัส RS485 เชื่อมไปยัง UNO Node (Lab 09):**

| ESP32 MAX485 | UNO MAX485 |
| :--- | :--- |
| A | A |
| B | B |
| GND | GND |

## Code (ESP32 Modbus Master)
```cpp
#include <ModbusMaster.h>

#define RX2 16
#define TX2 17
#define DE_RE 4
#define MODBUS_BAUD 9600
#define SLAVE_ID 1     // ตรงกับ UNO ใน Lab 09

ModbusMaster node;

// สลับโหมดส่ง/รับของ MAX485
void preTransmission()  { digitalWrite(DE_RE, HIGH); }
void postTransmission() { digitalWrite(DE_RE, LOW); }

void setup() {
  Serial.begin(115200);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);

  // ใช้ Serial2 ของ ESP32 สำหรับ Modbus
  Serial2.begin(MODBUS_BAUD, SERIAL_8N1, RX2, TX2);

  node.begin(SLAVE_ID, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  Serial.println("--- Lab 13: ESP32 Modbus Gateway ---");
}

void loop() {
  // อ่าน Holding Register 0..2 จาก Node
  uint8_t result = node.readHoldingRegisters(0, 3);

  if (result == node.ku8MBSuccess) {
    uint16_t sensor  = node.getResponseBuffer(0);
    uint16_t ledStat = node.getResponseBuffer(1);
    uint16_t counter = node.getResponseBuffer(2);

    Serial.println("✅ อ่านข้อมูลจาก Node สำเร็จ");
    Serial.print("  Sensor : "); Serial.println(sensor);
    Serial.print("  LED    : "); Serial.println(ledStat);
    Serial.print("  Counter: "); Serial.println(counter);
  } else {
    Serial.print("❌ อ่านไม่สำเร็จ (Modbus error code 0x");
    Serial.print(result, HEX); Serial.println(")");
  }

  delay(2000);   // Poll ทุก 2 วินาที
}
```

## ทดสอบการ "เขียน" กลับไปคุม Node (ทางเลือก)
Master สั่งเปิด LED ที่ Node ได้โดยเขียน Reg 1:
```cpp
node.writeSingleRegister(1, 1);   // 1 = เปิด LED, 0 = ปิด
```

## คำอธิบายโค้ด
- **preTransmission / postTransmission** เป็น callback ที่ ModbusMaster เรียกอัตโนมัติก่อน/หลังส่ง เพื่อสลับขา DE/RE ของ MAX485 — ไม่ต้องคุมเองเหมือน Lab 06
- `ku8MBSuccess` คือสถานะอ่านสำเร็จ ค่า error อื่นช่วย diagnose (เช่น timeout = Node ไม่ตอบ, CRC error = สัญญาณรบกวน)
- ใช้ `Serial2` (Hardware Serial) ของ ESP32 ซึ่งเสถียรกว่า SoftwareSerial มาก
- ข้อมูลที่อ่านได้ในตัวแปร `sensor/counter` จะถูกส่งต่อขึ้น OPS Server ใน **Lab 14**

## 🧪 โจทย์ท้าย Lab
1. เพิ่มการ Poll หลาย Node (Slave ID 1 และ 2) สลับกัน โดยเรียก `node.begin()` เปลี่ยน ID
2. นับ error rate: ถ้าอ่านไม่สำเร็จเกิน 5 ครั้งติด ให้พิมพ์เตือนว่า Node อาจหลุด
3. คำถาม: ทำไม Gateway ถึงสำคัญในสถาปัตยกรรม IIoT? อธิบายบทบาท "แปลภาษา" ระหว่าง Field Bus กับ Enterprise Network
