# Lab 11: เชื่อมต่อ WPA2-Enterprise (TBV-WiFi / Windows Login)

## Overview (ภาพรวม)
เครือข่ายระดับองค์กรมักไม่ใช้รหัสผ่าน Wi-Fi ร่วม (PSK) แต่ใช้ **WPA2-Enterprise** ที่ผู้ใช้แต่ละคนล็อกอินด้วย **Username + Password ของตัวเอง** (เช่น Windows / Active Directory Login) ผ่าน RADIUS Server วิธีนี้ปลอดภัยกว่า ติดตามผู้ใช้รายคนได้ และเพิกถอนสิทธิ์ทีละคนได้

ในแลปนี้ ESP32 จะเข้าเครือข่าย **TBV-WiFi** ด้วยโปรโตคอล **WPA2-Enterprise (PEAP/MSCHAPv2)** ซึ่งเป็นรูปแบบที่ใช้กับ Windows Login มากที่สุด นี่คือด่านสำคัญที่ทำให้ Gateway สามารถอยู่บนเครือข่ายองค์กรจริงและส่งข้อมูลเข้า OPS Server ได้

## ข้อมูลที่ต้องเตรียม (จากฝ่าย IT ของลูกค้า)
- **SSID:** `TBV-WiFi`
- **Identity / Username:** บัญชีโดเมน (เช่น `DOMAIN\username` หรือ `username@domain`)
- **Password:** รหัสผ่านของบัญชีนั้น
- รูปแบบ Authentication: **PEAP** (Outer) + **MSCHAPv2** (Inner) — รูปแบบมาตรฐานของ Windows
- โดยปกติ **ไม่ต้องใช้ใบรับรอง CA** สำหรับการทดสอบ (validate server = ปิด) แต่ในงาน production ฝ่าย IT อาจบังคับให้ตรวจ certificate

## Code (ESP32 Arduino Core 3.x ขึ้นไป)
```cpp
#include <WiFi.h>

const char* ssid     = "TBV-WiFi";
const char* identity = "DOMAIN\\username";   // บัญชี Windows/AD
const char* username = "DOMAIN\\username";   // ปกติเหมือน identity
const char* password = "YOUR_AD_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n--- Lab 11: WPA2-Enterprise ---");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);

  // เชื่อมต่อแบบ Enterprise (PEAP/MSCHAPv2)
  // overload นี้รองรับใน ESP32 core 3.x
  WiFi.begin(ssid, WPA2_AUTH_PEAP, identity, username, password);

  Serial.print("กำลังเข้าสู่เครือข่ายองค์กร");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 60) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ เข้าเครือข่ายองค์กรสำเร็จ");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  } else {
    Serial.println("\n❌ ล็อกอินไม่สำเร็จ ตรวจสอบ Username/Password หรือสิทธิ์บัญชี");
  }
}

void loop() {
  Serial.println(WiFi.status() == WL_CONNECTED ? "Online" : "Offline");
  delay(5000);
}
```

## ทางเลือก: ESP32 Core เวอร์ชันเก่า (2.x) ด้วย esp_wpa2.h
หาก `WiFi.begin(ssid, WPA2_AUTH_PEAP, ...)` คอมไพล์ไม่ผ่าน ให้ใช้วิธี API ระดับล่าง:
```cpp
#include <WiFi.h>
#include "esp_wpa2.h"

const char* ssid = "TBV-WiFi";
const char* EAP_IDENTITY = "DOMAIN\\username";
const char* EAP_USERNAME = "DOMAIN\\username";
const char* EAP_PASSWORD = "YOUR_AD_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t*)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t*)EAP_USERNAME, strlen(EAP_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t*)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.print("\nIP: "); Serial.println(WiFi.localIP());
}
void loop() {}
```

## คำอธิบายและจุดที่มักติด
- **Identity vs Username**: บางระบบ Identity (ที่ส่งแบบเปิด) ใช้ค่าทั่วไป (anonymous) ส่วน Username จริงอยู่ใน tunnel ที่เข้ารหัส — สำหรับ Windows ทั่วไปมักตั้งให้เหมือนกัน
- **รูปแบบชื่อบัญชี**: ลองทั้ง `DOMAIN\\username`, `username@domain.com`, และ `username` เปล่าๆ เพราะแต่ละองค์กรตั้งค่า RADIUS ต่างกัน (`\\` ในโค้ดคือ backslash หนึ่งตัว)
- ถ้าเชื่อมไม่ติด: ตรวจว่าบัญชีไม่ถูกล็อก, รหัสไม่หมดอายุ, และอุปกรณ์ MAC ไม่ถูกบล็อกโดย IT
- เก็บรหัสผ่านไว้ใน Lab 12 (Config Portal) แทนการ Hardcode เพื่อความปลอดภัยและสะดวกเปลี่ยน

## 🧪 โจทย์ท้าย Lab
1. ทดสอบใส่ Username ผิด แล้วดูว่าใช้เวลานานแค่ไหนกว่าจะ Timeout — ออกแบบ retry ให้เหมาะสม
2. แสดง MAC Address ของ ESP32 (`WiFi.macAddress()`) เพื่อให้ IT เพิ่มเข้า whitelist
3. คำถาม: ทำไมการ Hardcode รหัสผ่าน AD ลงในโค้ดจึงเป็นความเสี่ยงด้านความปลอดภัย? Lab 12 แก้ปัญหานี้อย่างไร?
