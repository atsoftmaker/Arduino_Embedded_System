# Lab 10: ESP32 Wi-Fi พื้นฐาน (Station Mode)

## Overview (ภาพรวม)
**ESP32** เป็นไมโครคอนโทรลเลอร์ที่มี Wi-Fi และ Bluetooth ในตัว ทำงานที่แรงดัน **3.3V** (ต่างจาก UNO ที่ 5V — ข้อควรระวังสำคัญ) ในแลปนี้เราเริ่มจากพื้นฐานที่สุด: การเชื่อมต่อ ESP32 เข้ากับ Wi-Fi แบบบ้าน/สำนักงานทั่วไป (WPA2-PSK ที่มีแค่รหัสผ่าน) เพื่อปูทางสู่ Enterprise Wi-Fi (Lab 11)

ผู้เรียนจะเข้าใจวงจรชีวิตการเชื่อมต่อ: ตั้งโหมด → เริ่มเชื่อม → รอจนได้ IP → ตรวจสอบสถานะ ซึ่งเป็นพื้นฐานของทุกงาน IoT

## ⚠️ ข้อควรระวังเรื่องแรงดันไฟ
> ESP32 ทำงานที่ **3.3V** ขา GPIO **ไม่ทนไฟ 5V** ห้ามต่อสัญญาณจาก UNO (5V) เข้า ESP32 โดยตรง ต้องผ่าน Logic Level Shifter หรือผ่านโมดูล RS485 (ดู Lab 13)

## Hardware
- บอร์ด ESP32 DevKit V1 + สาย USB
- ตั้งค่า Arduino IDE: ติดตั้ง ESP32 Board Package และเลือกบอร์ด "ESP32 Dev Module"

## Code
```cpp
#include <WiFi.h>

// แก้เป็นชื่อ Wi-Fi และรหัสผ่านของคุณ
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.print("กำลังเชื่อมต่อ Wi-Fi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);             // โหมด Station (เป็นลูกข่าย)
  WiFi.begin(ssid, password);

  // รอจนกว่าจะเชื่อมต่อสำเร็จ
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ เชื่อมต่อสำเร็จ!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\n❌ เชื่อมต่อไม่สำเร็จ ตรวจสอบ SSID/Password");
  }
}

void loop() {
  // ตรวจสอบสถานะการเชื่อมต่อทุก 5 วินาที
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Online | IP: "); Serial.print(WiFi.localIP());
    Serial.print(" | RSSI: "); Serial.println(WiFi.RSSI());
  } else {
    Serial.println("Offline - กำลังเชื่อมต่อใหม่...");
    WiFi.reconnect();
  }
  delay(5000);
}
```

## คำอธิบายโค้ด
- `WiFi.mode(WIFI_STA)` ตั้งให้ ESP32 เป็น Station (ลูกข่าย) — มีโหมด AP (จุดปล่อย) ที่ใช้ใน Lab 12 ด้วย
- ใช้ Baud Rate **115200** สำหรับ ESP32 (เร็วกว่า UNO)
- `WiFi.status()` คืนสถานะ เช่น `WL_CONNECTED`, `WL_DISCONNECTED` — ใช้ตรวจและ reconnect อัตโนมัติ
- `WiFi.RSSI()` บอกความแรงสัญญาณ (ยิ่งใกล้ 0 ยิ่งแรง เช่น -50 ดีกว่า -80)

## 🧪 โจทย์ท้าย Lab
1. เพิ่มการ Scan หา Wi-Fi รอบตัว (`WiFi.scanNetworks()`) แล้วแสดงรายชื่อ SSID พร้อมความแรงสัญญาณ
2. ทำ LED บนบอร์ด (GPIO2) ติดเมื่อ online และกระพริบเมื่อ offline
3. คำถาม: WPA2-PSK ต่างจาก WPA2-Enterprise อย่างไร? ทำไมองค์กรใหญ่จึงนิยม Enterprise?
