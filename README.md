# Lab: การพัฒนาระบบด้วย Embedded System – Arduino

ชุดเนื้อหาฝึกอบรมเชิงปฏิบัติการ **2 วัน** โดย **AtSoftMaker** 🚀
ครอบคลุมส่วน **ระบบควบคุม (Control Systems), การสื่อสารอุตสาหกรรม (RS485/Modbus) และ ESP32 Gateway** สำหรับส่งข้อมูลเข้าสู่ OPS Server

Repository นี้เป็น **ส่วนต่อยอด** จากพื้นฐานที่อบรมไปแล้ว เพื่อให้หลักสูตรครบถ้วนตามโครงสร้างที่แจ้งลูกค้า

---

## 🗺️ แผนผังหลักสูตร และสถานะเนื้อหา

| ช่วง | หัวข้อในหลักสูตร | สถานะ | อยู่ที่ |
| :--- | :--- | :--- | :--- |
| วันที่ 1 – ช่วงเช้า | **Lab 1-3**: พื้นฐานภาษา C (Variables, Control Structures, Functions) | ✅ ทำแล้ว | [C_Arduino_Lab](https://github.com/gatunyus/C_Arduino_Lab) |
| วันที่ 1 – ช่วงเช้า | **Digital & Analog I/O** พื้นฐาน (อ่านเซนเซอร์ดิจิทัล/อนาล็อก) | ✅ ทำแล้ว | [Lab_Arduino_UNO](https://github.com/gatunyus/Lab_Arduino_UNO) |
| วันที่ 1 – ช่วงเช้า | **Lab 4**: ควบคุม Digital Output (LED + Relay 220V) | 🟢 ในชุดนี้ | `Day1/Lab04` |
| วันที่ 1 – ช่วงเช้า | **Lab 5**: อ่าน Analog (VR) + สร้าง Control Line | 🟢 ในชุดนี้ | `Day1/Lab05` |
| วันที่ 1 – ช่วงบ่าย | **Lab 5.1**: Open Loop Control (สั่งงานตามเวลา) | 🟢 ในชุดนี้ | `Day1/Lab05.1` |
| วันที่ 1 – ช่วงบ่าย | **Lab 5.2**: Closed Loop Control (สั่งงานตาม Feedback) | 🟢 ในชุดนี้ | `Day1/Lab05.2` |
| วันที่ 1 – ช่วงบ่าย | **Lab 5.3**: PID เบื้องต้น (ควบคุมแบบหรี่กำลัง PWM) | 🟢 ในชุดนี้ | `Day1/Lab05.3` |
| วันที่ 1 – ช่วงบ่าย | **Lab 6-8**: RS485 + คำสั่งแบบ Master/Slave | 🟢 ในชุดนี้ | `Day1/Lab06-08` |
| วันที่ 1 – ช่วงบ่าย | **Lab 9**: Modbus RTU Slave | 🟢 ในชุดนี้ | `Day1/Lab09` |
| วันที่ 2 – ช่วงเช้า | **Lab 10-11**: ESP32 Wi-Fi + WPA2-Enterprise (TBV-WiFi) | 🟢 ในชุดนี้ | `Day2/Lab10-11` |
| วันที่ 2 – ช่วงเช้า | **Lab 12**: Web Config Portal (Dynamic Provisioning) | 🟢 ในชุดนี้ | `Day2/Lab12` |
| วันที่ 2 – ช่วงบ่าย | **Lab 13**: ESP32 Gateway ดึงข้อมูลจาก Node ผ่าน RS485 | 🟢 ในชุดนี้ | `Day2/Lab13` |
| วันที่ 2 – ช่วงบ่าย | **Lab 14**: ส่ง Alert + Data Packet เข้า OPS Server (Realtime) | 🟢 ในชุดนี้ | `Day2/Lab14` |

> 🟢 = เนื้อหาที่จัดทำเพิ่มในชุดนี้   ✅ = อบรม/ส่งมอบไปแล้วใน repo เดิม

---

## 📂 โครงสร้าง Repository

```
Lab_Embedded_System/
├── README.md                        ← ไฟล์นี้
├── INSTRUCTOR_GUIDE.md              ← คู่มือวิทยากร (timing, จุดที่ผู้เรียนมักติด, เฉลย)
│
├── Day1_Control_Communication/      ← ใช้บอร์ด Arduino UNO / MEGA (ลอจิก 5V)
│   ├── Lab04_Relay_Control/
│   ├── Lab05_Analog_VR_ControlLine/
│   ├── Lab05.1_Open_Loop_Control/
│   ├── Lab05.2_Closed_Loop_Control/
│   ├── Lab05.3_PID_Intro/
│   ├── Lab06_RS485_Basic/
│   ├── Lab07_RS485_Master_Slave/
│   ├── Lab08_RS485_MultiDrop/
│   └── Lab09_Modbus_RTU_Slave/
│
└── Day2_ESP32_Gateway/              ← ใช้บอร์ด ESP32 (เชื่อมต่อเครือข่าย)
    ├── Lab10_WiFi_Basic/
    ├── Lab11_WPA2_Enterprise/
    ├── Lab12_WiFi_Config_Portal/
    ├── Lab13_ESP32_Gateway_RS485/
    └── Lab14_DataLogging_OPS/
```

แต่ละโฟลเดอร์ Lab จะมี `instruction.md` (Overview, การต่อวงจร, โค้ด, คำอธิบาย, โจทย์ท้าย Lab) และไฟล์โค้ด `.ino`

---

## 🛠️ อุปกรณ์ที่ใช้ (Hardware)

**วันที่ 1 (UNO/MEGA – 5V)**
- Arduino UNO R3 และ/หรือ MEGA 2560 (อย่างน้อย 2 บอร์ดต่อกลุ่ม สำหรับ Lab RS485)
- โมดูล Relay 1-2 Channel (ขับโหลด 220V) — **ระวังไฟ AC**
- ตัวต้านทานปรับค่าได้ (Potentiometer / VR) 10kΩ
- โมดูล RS485 (MAX485 / MAX3485) 2 ตัวขึ้นไป
- LED, ตัวต้านทาน 220Ω–1kΩ, สาย Jumper, Breadboard

**วันที่ 2 (ESP32)**
- บอร์ด ESP32 DevKit V1 (หรือเทียบเท่า)
- โมดูล RS485 (MAX485) สำหรับฝั่ง Gateway
- เครือข่ายทดสอบที่จำลอง WPA2-Enterprise และ OPS Server (IP 10.5.15.5)

## 💻 ซอฟต์แวร์ (Prerequisites)
- [Arduino IDE](https://www.arduino.cc/en/software) (แนะนำ 2.x)
- ESP32 Board Package (Boards Manager → `esp32 by Espressif`)
- ไลบรารีที่ใช้: `ModbusMaster`, `ArduinoModbus` / `ModbusRTUSlave`, `Preferences` (มากับ ESP32), `WiFi`, `WebServer`, `HTTPClient`, `ArduinoJson`
- ไดรเวอร์ USB-Serial `CH34x` (กรณีอัปโหลดไม่ได้ — มีในrepo เดิม `Lab_Arduino_UNO`)

---

## ⚠️ ความปลอดภัย (Safety First)
- งานที่เกี่ยวกับ **Relay 220V (ไฟ AC)** ให้ทำภายใต้การดูแลของวิทยากรเท่านั้น ตัดไฟก่อนต่อวงจรทุกครั้ง
- **อย่าต่อสัญญาณ 5V (UNO) เข้าขา ESP32 โดยตรง** — ESP32 ทำงานที่ 3.3V ต้องผ่าน Logic Level Shifter หรือใช้โมดูล RS485 เป็นตัวกลาง
- ตรวจสอบขั้ว A/B ของบัส RS485 และต่อ GND ร่วม (Common Ground) ทุกครั้ง

---

**จัดทำโดย:** AtSoftMaker — ห้างหุ้นส่วนจำกัด แอทซอฟท์เมกเกอร์
