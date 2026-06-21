# Lab 22: จำลองบอร์ดเป็น Modbus RTU Slave

## Overview (ภาพรวม)
**Modbus RTU** คือโปรโตคอลสื่อสารมาตรฐานอุตสาหกรรมที่ใช้แพร่หลายที่สุดในโลก ทำงานบนสายฟิสิคัล RS485 (จาก Lab 19–08) แต่ใช้รูปแบบ Frame แบบ binary ที่มี **Slave ID, Function Code, Register Address, Data และ CRC-16** ตรวจสอบความถูกต้อง ทำให้น่าเชื่อถือกว่าการส่งข้อความ ASCII เอง

อุปกรณ์อุตสาหกรรมเกือบทั้งหมด (PLC, Power Meter, Inverter, Sensor Transmitter) พูด Modbus ได้ ในแลปนี้เราจะทำให้ **Arduino UNO กลายเป็น Modbus RTU Slave** ที่มี Register ให้ Master อ่าน/เขียน เปรียบเสมือนทำให้บอร์ดของเรากลายเป็น "อุปกรณ์อุตสาหกรรม" หนึ่งตัวที่ SCADA หรือ ESP32 Gateway (Lab 26) มาดึงข้อมูลได้

### ตารางรีจิสเตอร์ (Register Map) ของ Slave ตัวนี้
| Register | ชนิด | ความหมาย |
| :--- | :--- | :--- |
| Holding Reg 0 | อ่าน | ค่าเซนเซอร์ (จาก VR ที่ A0, 0–1023) |
| Holding Reg 1 | อ่าน/เขียน | สถานะ LED (0 = OFF, 1 = ON) |
| Holding Reg 2 | อ่าน | ตัวนับ (counter เพิ่มขึ้นเรื่อยๆ) |

## ไลบรารีที่ต้องติดตั้ง
ติดตั้งผ่าน Arduino IDE → Library Manager:
- **ModbusRTUSlave** (โดย CMB27) — ใช้งานง่าย รองรับ SoftwareSerial และขา DE/RE
- **SoftwareSerial** (มากับ Arduino อยู่แล้ว)

## Hardware Wiring (การต่อวงจร)
ต่อ MAX485 เหมือน Lab 19 ทุกประการ:

| MAX485 | Arduino UNO |
| :--- | :--- |
| DI | **D3** |
| RO | **D2** |
| DE + RE | **D4** |
| VCC / GND | 5V / GND |

| อุปกรณ์เพิ่ม | Arduino UNO |
| :--- | :--- |
| VR (เซนเซอร์จำลอง) | **A0** |
| LED ผ่าน R 220Ω | **D7** |

## Code (Modbus RTU Slave บน UNO)
```cpp
#include <ModbusRTUSlave.h>
#include <SoftwareSerial.h>

// --- กำหนดขา ---
const byte rxPin = 2;   // RO
const byte txPin = 3;   // DI
const byte dePin = 4;   // DE+RE
const byte ledPin = 7;
const byte sensorPin = A0;

const byte SLAVE_ID = 1;        // Modbus Slave Address
const unsigned long BAUD = 9600;

SoftwareSerial mbSerial(rxPin, txPin);
ModbusRTUSlave modbus(mbSerial, dePin);

// --- พื้นที่ Holding Registers (3 ตัว) ---
uint16_t holdingRegisters[3];

unsigned long lastTick = 0;
uint16_t counter = 0;

void setup() {
  pinMode(ledPin, OUTPUT);

  // ผูก array รีจิสเตอร์เข้ากับ Modbus
  modbus.configureHoldingRegisters(holdingRegisters, 3);
  modbus.begin(SLAVE_ID, BAUD);
}

void loop() {
  // 1) อัปเดตค่าเซนเซอร์ลง Reg 0
  holdingRegisters[0] = analogRead(sensorPin);

  // 2) อัปเดตตัวนับลง Reg 2 ทุก 1 วินาที
  if (millis() - lastTick >= 1000) {
    lastTick = millis();
    counter++;
    holdingRegisters[2] = counter;
  }

  // 3) ประมวลผลคำขอ Modbus จาก Master (สำคัญสุด ต้องเรียกบ่อยๆ)
  modbus.poll();

  // 4) ให้ Master เขียน Reg 1 มาควบคุม LED
  digitalWrite(ledPin, holdingRegisters[1] ? HIGH : LOW);
}
```

## คำอธิบายโค้ด
- `configureHoldingRegisters()` ผูก array ของเราเข้ากับ Modbus — Master อ่าน/เขียนค่าตรงนี้ได้ (Function Code 03 = Read Holding, 06/16 = Write)
- `modbus.poll()` ต้องถูกเรียกใน `loop()` บ่อยที่สุด เพราะมันคอยฟังและตอบ Frame จาก Master — **ห้ามใส่ `delay()` นานๆ คั่น** มิฉะนั้นจะตอบไม่ทัน (Timeout)
- ไลบรารีจัดการเรื่อง CRC-16, การควบคุมขา DE/RE และการ Parse Frame ให้อัตโนมัติ
- บอร์ดนี้พร้อมให้ **ESP32 Gateway ใน Lab 26** มาดึงข้อมูลผ่าน Modbus ได้ทันที

## การทดสอบ
ทดสอบได้ 2 ทาง:
1. ใช้โปรแกรมบนคอม เช่น **Modbus Poll** หรือ **QModMaster** ต่อผ่าน USB-RS485 converter อ่าน Holding Register 0–2 ของ Slave ID 1
2. รอใช้คู่กับ Lab 26 (ESP32 เป็น Modbus Master)

## 🧪 โจทย์ท้าย Lab
1. เพิ่ม Holding Register 3 เก็บค่าอุณหภูมิจากเซนเซอร์จริง (DS18B20 จาก Lab_Arduino_UNO)
2. เปลี่ยน `SLAVE_ID` เป็น 2 แล้วทดสอบว่ามี Slave หลายตัวบนบัสเดียวกันได้ (เชื่อมกับ Lab 21)
3. คำถาม: CRC-16 ใน Modbus มีไว้ทำอะไร? ถ้า Frame ผิดเพี้ยนระหว่างทาง Slave จะทำอย่างไร?

