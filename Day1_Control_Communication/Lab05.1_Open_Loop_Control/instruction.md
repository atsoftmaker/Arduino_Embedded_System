# Lab 05.1: ระบบควบคุมแบบเปิด (Open Loop Control)

## Overview (ภาพรวม)
**Open Loop Control** คือระบบควบคุมที่สั่งงานตามคำสั่งที่ตั้งไว้ล่วงหน้า **โดยไม่สนใจผลลัพธ์จริง (ไม่มี Feedback)** ตัวอย่างคลาสสิกคือ "เครื่องซักผ้า" ที่ปั่นตามเวลาที่ตั้ง ไม่ว่าผ้าจะสะอาดหรือยัง หรือ "ไฟจราจร" ที่เปลี่ยนสีตามเวลา

ในแลปนี้เราจะจำลองระบบรดน้ำต้นไม้/ปั๊มน้ำอัตโนมัติที่สั่งงาน Relay ตามตารางเวลา และเรียนรู้การใช้ `millis()` แทน `delay()` เพื่อให้ระบบทำงานหลายอย่างพร้อมกันได้ (Non-blocking) ซึ่งสำคัญมากสำหรับระบบควบคุมจริง

## Hardware Wiring (การต่อวงจร)

| อุปกรณ์ | Arduino UNO |
| :--- | :--- |
| Relay IN1 (จำลองปั๊ม/วาล์ว) | **D8** |
| LED แสดงสถานะ ON | **D13** (LED บนบอร์ด) |

## Code
```cpp
// Lab 05.1: Open Loop Control - สั่งงานตามเวลา (Non-blocking ด้วย millis)
const int relayPin = 8;
const int RELAY_ON  = LOW;   // ปรับตามชนิด Relay
const int RELAY_OFF = HIGH;

// ตั้งเวลาทำงาน (มิลลิวินาที)
const unsigned long ON_DURATION  = 5000;   // ปั๊มทำงาน 5 วินาที
const unsigned long OFF_DURATION = 10000;  // หยุดพัก 10 วินาที

unsigned long previousMillis = 0;
bool pumpState = false;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);
  Serial.println("--- Lab 05.1: Open Loop Control ---");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long interval = pumpState ? ON_DURATION : OFF_DURATION;

  // ถึงเวลาสลับสถานะหรือยัง?
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    pumpState = !pumpState;   // สลับสถานะ

    if (pumpState) {
      digitalWrite(relayPin, RELAY_ON);
      Serial.println(">> ปั๊มทำงาน (ON) ตามเวลาที่ตั้งไว้");
    } else {
      digitalWrite(relayPin, RELAY_OFF);
      Serial.println(">> ปั๊มหยุด (OFF) รอรอบถัดไป");
    }
  }

  // ส่วนนี้ทำงานต่อได้เรื่อยๆ เพราะไม่มี delay() มาบล็อก
}
```

## คำอธิบายโค้ด
- **ไม่มี Sensor / Feedback** — ระบบตัดสินใจจาก "เวลา" เพียงอย่างเดียว นี่คือนิยามของ Open Loop
- ใช้ `millis()` (นาฬิกานับเวลาตั้งแต่บอร์ดเริ่มทำงาน) เปรียบเทียบกับ `previousMillis` แทน `delay()` ทำให้ CPU ไม่ค้าง สามารถอ่านปุ่ม/Serial อื่นๆ ได้พร้อมกัน
- ข้อจำกัด: ถ้าน้ำในถังหมด ปั๊มก็ยังสั่งทำงานต่อ เพราะระบบ "ไม่รู้" สถานะจริง → นำไปสู่ Lab 5.2 (Closed Loop)

## 🧪 โจทย์ท้าย Lab
1. เพิ่มรอบการทำงาน 3 ช่วงเวลาในหนึ่งวัน (จำลองด้วยวินาที) โดยใช้ตัวแปรนับรอบ
2. เพิ่ม LED สีเขียว/แดง แสดงสถานะ ON/OFF แบบ Non-blocking
3. คำถาม: ยกตัวอย่างอุปกรณ์ในโรงงาน 2 ชิ้นที่เป็น Open Loop และอธิบายว่าทำไมถึงไม่จำเป็นต้องมี Feedback
