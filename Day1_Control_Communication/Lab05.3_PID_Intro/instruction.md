# Lab 05.3: ระบบควบคุมแบบ PID เบื้องต้น (ควบคุมแบบหรี่กำลัง)

## Overview (ภาพรวม)
**PID Control** (Proportional–Integral–Derivative) คือหัวใจของระบบควบคุมอุตสาหกรรมสมัยใหม่ ต่างจาก On/Off ตรงที่ PID ปรับ "กำลังขับ" แบบต่อเนื่อง (Analog/PWM) ตามขนาดของ Error ทำให้ระบบเข้าสู่เป้าหมายได้นุ่มนวล แม่นยำ และไม่แกว่ง

สูตรพื้นฐาน:
```
Output = (Kp × Error) + (Ki × ∫Error dt) + (Kd × dError/dt)
```
- **P (Proportional)** — แก้ตามขนาด Error ปัจจุบัน (Error มาก ดันแรง)
- **I (Integral)** — สะสม Error ที่ค้างนานๆ เพื่อกำจัด Steady-State Error
- **D (Derivative)** — ดูแนวโน้มการเปลี่ยนแปลง เพื่อลด Overshoot/หน่วงการพุ่งเกิน

ในแลปนี้เราจะคุมความสว่าง LED (จำลอง Heater หรี่กำลัง) ให้เซนเซอร์แสง/VR เข้าสู่ค่าเป้าหมาย โดยเขียน PID เองเพื่อให้เข้าใจกลไก (ไม่ใช้ไลบรารี)

## Hardware Wiring (การต่อวงจร)

| อุปกรณ์ | Arduino UNO | บทบาท |
| :--- | :--- | :--- |
| VR ขากลาง | **A0** | จำลอง Process Value (เซนเซอร์) |
| LED ผ่าน R 220Ω | **D9 (~PWM)** | Actuator หรี่กำลัง |

> งานจริง: A0 = เซนเซอร์อุณหภูมิ, D9 = สัญญาณ PWM ไปขับ SSR (Solid State Relay) เพื่อหรี่กำลัง Heater

## Code
```cpp
// Lab 05.3: PID Control เบื้องต้น (เขียนเอง ไม่ใช้ไลบรารี)
const int sensorPin = A0;
const int outputPin = 9;   // PWM

// ----- ค่าเป้าหมาย -----
float setPoint = 50.0;     // เป้าหมาย (0-100)

// ----- ค่าเกน PID (ปรับจูนตามระบบ) -----
float Kp = 4.0;
float Ki = 0.2;
float Kd = 1.0;

// ----- ตัวแปรสะสมสำหรับ I และ D -----
float integral = 0;
float lastError = 0;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  lastTime = millis();
  Serial.println("--- Lab 05.3: PID Control ---");
}

void loop() {
  // 1) เวลาที่ผ่านไปจริง (dt) หน่วยวินาที
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  if (dt <= 0) dt = 0.001;

  // 2) อ่าน Process Value แล้วคำนวณ Error
  int raw = analogRead(sensorPin);
  float pv = map(raw, 0, 1023, 0, 100);
  float error = setPoint - pv;

  // 3) คำนวณแต่ละเทอม
  float P = Kp * error;
  integral += error * dt;
  float I = Ki * integral;
  float derivative = (error - lastError) / dt;
  float D = Kd * derivative;

  // 4) รวมผลและจำกัดช่วง (0-255 สำหรับ PWM)
  float output = P + I + D;
  output = constrain(output, 0, 255);

  // 5) Anti-windup ง่ายๆ: จำกัดค่าสะสมไม่ให้บานปลาย
  integral = constrain(integral, -500, 500);

  // 6) ส่งออกไปยัง Actuator
  analogWrite(outputPin, (int)output);

  // 7) เก็บค่าไว้รอบถัดไป + แสดงผล
  lastError = error;
  lastTime = now;

  Serial.print("SP:"); Serial.print(setPoint);
  Serial.print(" PV:"); Serial.print(pv);
  Serial.print(" Err:"); Serial.print(error);
  Serial.print(" Out:"); Serial.println(output);

  delay(50);
}
```

## คำอธิบายโค้ด
- เราคำนวณ `dt` จาก `millis()` จริง เพื่อให้เทอม I และ D ถูกต้องตามเวลา
- `constrain()` จำกัดเอาต์พุตให้อยู่ในช่วง PWM (0–255) และทำ **Anti-windup** กันค่า Integral สะสมจนระบบควบคุมไม่ได้
- การปรับจูน (Tuning): เริ่มจาก Kp อย่างเดียวก่อน เพิ่มจนระบบเริ่มแกว่ง แล้วค่อยเติม Kd ลด Overshoot และเติม Ki กำจัด Error คงค้าง
- หลักสูตรนี้เป็น "เบื้องต้น" — ในงานจริงนิยมใช้ไลบรารี `PID_v1` (โดย Brett Beauregard) ซึ่งจัดการ dt และ anti-windup ให้

## 🧪 โจทย์ท้าย Lab
1. ทดลองตั้ง Ki=0, Kd=0 (เหลือแต่ P) แล้วสังเกตว่ามี Steady-State Error หรือไม่
2. เพิ่ม Kp มากๆ แล้วดูอาการ Overshoot / Oscillation
3. คำถาม: ในระบบควบคุมอุณหภูมิเตาอบ เทอมไหน (P/I/D) สำคัญที่สุดในการกำจัดความคลาดเคลื่อนคงค้าง? เพราะอะไร?
