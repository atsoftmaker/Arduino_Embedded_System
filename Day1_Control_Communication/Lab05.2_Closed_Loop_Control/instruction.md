# Lab 05.2: ระบบควบคุมแบบปิด (Closed Loop Control)

## Overview (ภาพรวม)
**Closed Loop Control** (หรือ Feedback Control) คือระบบที่ **วัดผลลัพธ์จริงด้วยเซนเซอร์** แล้วนำมาเปรียบเทียบกับค่าเป้าหมาย (Set Point) เพื่อตัดสินใจสั่งงาน ต่างจาก Open Loop ตรงที่ระบบ "รับรู้" สภาพจริงและปรับตัวได้

ในแลปนี้เราจะจำลองระบบควบคุมอุณหภูมิ/ระดับ แบบ **On-Off Control (Bang-Bang)** ที่พบบ่อยที่สุดในอุตสาหกรรม เช่น ตู้เย็น เครื่องทำน้ำอุ่น เทอร์โมสตัท โดยใช้ VR จำลองเซนเซอร์ (ค่าที่อ่านได้ = ค่าปัจจุบันของระบบ) และใช้ Relay จำลองตัวทำความร้อน/ปั๊ม

แนวคิดหลัก: **Error = Set Point − Process Value** ถ้าค่าจริงต่ำกว่าเป้า → สั่งทำงาน, ถ้าถึงเป้าแล้ว → สั่งหยุด พร้อมใส่ **Hysteresis (ช่วงเผื่อ)** เพื่อกัน Relay สลับถี่เกินไป

## Hardware Wiring (การต่อวงจร)

| อุปกรณ์ | Arduino UNO | บทบาท |
| :--- | :--- | :--- |
| VR ขากลาง | **A0** | จำลองเซนเซอร์ (Process Value) |
| Relay IN1 | **D8** | จำลอง Heater/ปั๊ม (Actuator) |
| LED เขียว | **D6** | แสดงว่าอยู่ในเป้าหมาย |
| LED แดง | **D7** | แสดงว่ากำลังเร่งเข้าหาเป้า |

> ในงานจริง A0 จะต่อกับเซนเซอร์อุณหภูมิ (เช่น DS18B20 จาก `Lab_Arduino_UNO` Lab10) แต่ในแลปนี้ใช้ VR หมุนมือเพื่อให้เห็นพฤติกรรมการควบคุมชัดเจน

## Code
```cpp
// Lab 05.2: Closed Loop Control - On/Off Control พร้อม Hysteresis
const int sensorPin = A0;   // จำลองเซนเซอร์ด้วย VR
const int relayPin  = 8;
const int ledGreen  = 6;
const int ledRed    = 7;

const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

// ค่าเป้าหมาย และช่วงเผื่อ (หน่วยสมมติ 0-100)
const float SET_POINT  = 50.0;
const float HYSTERESIS = 3.0;   // เผื่อ +/- 3 หน่วย

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);
  Serial.println("--- Lab 05.2: Closed Loop (On/Off) Control ---");
}

void loop() {
  // 1) อ่านค่าปัจจุบันจากเซนเซอร์ แล้วสเกลเป็น 0-100
  int raw = analogRead(sensorPin);
  float processValue = map(raw, 0, 1023, 0, 100);

  // 2) คำนวณ Error
  float error = SET_POINT - processValue;

  // 3) ตัดสินใจแบบ On/Off + Hysteresis
  if (processValue < SET_POINT - HYSTERESIS) {
    digitalWrite(relayPin, RELAY_ON);    // ต่ำกว่าเป้า -> เร่งทำงาน
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  } else if (processValue > SET_POINT + HYSTERESIS) {
    digitalWrite(relayPin, RELAY_OFF);   // เกินเป้า -> หยุด
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
  } else {
    // อยู่ในช่วงเป้าหมาย -> คงสถานะ ไฟเขียวติด
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  // 4) แสดงผล
  Serial.print("SetPoint: "); Serial.print(SET_POINT);
  Serial.print(" | Current: "); Serial.print(processValue);
  Serial.print(" | Error: "); Serial.println(error);

  delay(300);
}
```

## คำอธิบายโค้ด
- **Feedback Loop**: `analogRead()` คือการ "วัดผลจริง" แล้วป้อนกลับเข้าระบบ — นี่คือสิ่งที่ Open Loop ไม่มี
- **Hysteresis** ป้องกันอาการ Relay กระพริบถี่ (Chattering) เมื่อค่าจริงแกว่งอยู่รอบ Set Point — เป็นเทคนิคสำคัญในงานจริง
- ข้อจำกัดของ On/Off: ค่าจะแกว่งรอบเป้าเสมอ (Oscillation) ควบคุมละเอียดไม่ได้ → นำไปสู่ Lab 5.3 (PID)

## 🧪 โจทย์ท้าย Lab
1. ปรับ `SET_POINT` และ `HYSTERESIS` แล้วสังเกตพฤติกรรมการแกว่งของระบบ
2. แทนที่ VR ด้วยเซนเซอร์ DS18B20 (จาก Lab_Arduino_UNO Lab10) เพื่อควบคุมอุณหภูมิจริง
3. คำถาม: ถ้า Hysteresis เป็น 0 จะเกิดอะไรขึ้นกับ Relay? และถ้าตั้งกว้างเกินไปจะส่งผลอย่างไรต่อความแม่นยำ?
