# Lab 05: อ่านค่า Analog (VR) และการสร้าง Control Line

## Overview (ภาพรวม)
แลปนี้ผู้เรียนจะอ่านค่าจาก **ตัวต้านทานปรับค่าได้ (Potentiometer / VR)** ผ่านขา Analog Input ด้วย `analogRead()` ซึ่งให้ค่าความละเอียด 10-bit (`0–1023`) จากนั้นนำค่าที่อ่านได้มา **แปลงสเกล (Mapping)** ให้กลายเป็น "Control Line" — สัญญาณควบคุมที่ใช้กำหนดระดับการทำงานของอุปกรณ์ Output เช่น ความสว่างของ LED หรือระดับกำลังของโหลด

แนวคิด Control Line คือหัวใจของระบบควบคุมแบบปรับค่าได้ (Proportional) ที่จะต่อยอดไปสู่ Lab 5.1–5.3 โดยการหมุน VR เปรียบเสมือน "Set Point" ที่ผู้ใช้กำหนด

## Hardware Wiring (การต่อวงจร)

| Potentiometer (VR) | Arduino UNO |
| :--- | :--- |
| ขาซ้าย (1) | 5V |
| ขากลาง (2 / Wiper) | **A0** |
| ขาขวา (3) | GND |

| LED (Output) | Arduino UNO |
| :--- | :--- |
| ขั้วบวก (Anode) ผ่าน R 220Ω | **D9** (รองรับ PWM ~) |
| ขั้วลบ (Cathode) | GND |

> ขา D9 ของ UNO รองรับ PWM (สัญลักษณ์ `~`) จึงใช้ `analogWrite()` หรี่ไฟได้

## Code
```cpp
// Lab 05: อ่าน VR แล้วสร้าง Control Line คุมความสว่าง LED
const int vrPin  = A0;   // ตัวต้านทานปรับค่าได้
const int ledPin = 9;    // LED ขา PWM

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("--- Lab 05: Analog VR -> Control Line ---");
}

void loop() {
  // 1) อ่านค่าดิบจาก VR (0 - 1023)
  int rawValue = analogRead(vrPin);

  // 2) แปลงสเกลเป็น Control Line สำหรับ PWM (0 - 255)
  int controlLine = map(rawValue, 0, 1023, 0, 255);

  // 3) แปลงเป็นเปอร์เซ็นต์เพื่อให้คนอ่านเข้าใจง่าย (0 - 100%)
  int percent = map(rawValue, 0, 1023, 0, 100);

  // 4) ส่ง Control Line ออกไปคุมความสว่าง LED
  analogWrite(ledPin, controlLine);

  // 5) แสดงผล
  Serial.print("Raw: ");          Serial.print(rawValue);
  Serial.print("  | Control: ");  Serial.print(controlLine);
  Serial.print("  | Power: ");    Serial.print(percent);
  Serial.println(" %");

  delay(200);
}
```

## คำอธิบายโค้ด
- `analogRead()` คืนค่า 0–1023 (10-bit ADC) ตามแรงดันที่ขา A0 (0–5V)
- `map(value, fromLow, fromHigh, toLow, toHigh)` คือฟังก์ชันแปลงช่วงค่าเชิงเส้น — เปลี่ยน 0–1023 ให้เป็น 0–255 สำหรับ PWM
- `analogWrite()` สร้างสัญญาณ PWM (Pulse Width Modulation) เพื่อ "หรี่กำลัง" — ค่ายิ่งมาก Duty Cycle ยิ่งสูง LED ยิ่งสว่าง
- ค่า **Control Line** นี้คือสิ่งที่จะถูกนำไปใช้เป็นตัวแปรสั่งงานในระบบควบคุมขั้นต่อไป

## 🧪 โจทย์ท้าย Lab
1. เปลี่ยนจาก LED เป็นการพิมพ์ "ระดับความเร็วพัดลม 1–5" โดยแบ่งช่วงค่า VR ออกเป็น 5 ระดับ
2. เพิ่มการกรองสัญญาณรบกวน (Noise) ด้วยการเฉลี่ยค่า 10 ครั้ง (Moving Average) ก่อนนำไปใช้
3. คำถาม: ถ้าต้องการความละเอียดมากกว่า 10-bit ต้องทำอย่างไร? และ ESP32 มี ADC กี่ bit?
