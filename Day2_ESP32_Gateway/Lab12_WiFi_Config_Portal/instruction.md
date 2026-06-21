# Lab 12: Web Configuration Portal (Dynamic Provisioning)

## Overview (ภาพรวม)
ปัญหาของ Lab 10–11 คือเรา **Hardcode** ชื่อ Wi-Fi และรหัสผ่านลงในโค้ด ซึ่ง (1) ไม่ปลอดภัย (2) ต้องแก้โค้ดและ upload ใหม่ทุกครั้งที่เปลี่ยนรหัส แลปนี้แก้ปัญหาด้วยการสร้าง **Web Config Portal**:

1. เมื่อเปิดเครื่องครั้งแรก (หรือกดปุ่ม Reset Config) ESP32 จะปล่อย Wi-Fi ของตัวเอง (Access Point) ชื่อ `ESP32-Setup`
2. ผู้ติดตั้งใช้มือถือ/โน้ตบุ๊กเชื่อมต่อ แล้วเปิดเบราว์เซอร์ไปที่ `192.168.4.1`
3. กรอก SSID / Username / Password ผ่านหน้าเว็บ แล้วกด Save
4. ESP32 บันทึกค่าลง **หน่วยความจำถาวร (NVS / Preferences)** แล้วรีบูตเชื่อมต่ออัตโนมัติ

ค่าที่บันทึกจะอยู่แม้ปิดไฟ ทำให้ติดตั้งหน้างานได้โดยไม่ต้องต่อคอม — เป็นมาตรฐานของอุปกรณ์ IoT เชิงพาณิชย์

## ไลบรารีที่ใช้ (มากับ ESP32 Core อยู่แล้ว)
- `WiFi.h`, `WebServer.h`, `Preferences.h`

## Hardware
- ESP32 DevKit
- (ทางเลือก) ปุ่มกดที่ GPIO 0 (ปุ่ม BOOT บนบอร์ด) สำหรับสั่งล้างค่าและเข้าโหมดตั้งค่าใหม่

## Code
```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

WebServer server(80);
Preferences prefs;

const char* AP_SSID = "ESP32-Setup";
const char* AP_PASS = "12345678";       // รหัสเข้า AP ตอนตั้งค่า
const int   RESET_BTN = 0;              // ปุ่ม BOOT

String cfg_ssid, cfg_user, cfg_pass;

// ---------- หน้าเว็บฟอร์ม ----------
String htmlForm() {
  String h = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  h += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  h += "<title>ESP32 Setup</title></head><body style='font-family:sans-serif;max-width:420px;margin:40px auto;'>";
  h += "<h2>ตั้งค่าเครือข่าย ESP32</h2>";
  h += "<form action='/save' method='POST'>";
  h += "SSID:<br><input name='ssid' value='" + cfg_ssid + "' style='width:100%;padding:8px'><br><br>";
  h += "Username (Enterprise):<br><input name='user' value='" + cfg_user + "' style='width:100%;padding:8px'><br><br>";
  h += "Password:<br><input name='pass' type='password' style='width:100%;padding:8px'><br><br>";
  h += "<button type='submit' style='padding:10px 20px'>บันทึก & เชื่อมต่อ</button>";
  h += "</form></body></html>";
  return h;
}

void handleRoot() { server.send(200, "text/html", htmlForm()); }

void handleSave() {
  cfg_ssid = server.arg("ssid");
  cfg_user = server.arg("user");
  cfg_pass = server.arg("pass");

  // บันทึกลง NVS
  prefs.begin("netcfg", false);
  prefs.putString("ssid", cfg_ssid);
  prefs.putString("user", cfg_user);
  prefs.putString("pass", cfg_pass);
  prefs.end();

  server.send(200, "text/html",
    "<h3>บันทึกแล้ว กำลังรีบูตเพื่อเชื่อมต่อ...</h3>");
  delay(1500);
  ESP.restart();
}

// ---------- เริ่มโหมดตั้งค่า (AP + Web) ----------
void startConfigPortal() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.print("เข้าโหมดตั้งค่า | ต่อ Wi-Fi '"); Serial.print(AP_SSID);
  Serial.print("' แล้วเปิด http://"); Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.begin();
}

// ---------- พยายามเชื่อมต่อด้วยค่าที่บันทึกไว้ ----------
bool tryConnect() {
  prefs.begin("netcfg", true);
  cfg_ssid = prefs.getString("ssid", "");
  cfg_user = prefs.getString("user", "");
  cfg_pass = prefs.getString("pass", "");
  prefs.end();

  if (cfg_ssid == "") return false;   // ยังไม่เคยตั้งค่า

  WiFi.mode(WIFI_STA);
  if (cfg_user != "") {
    // มี Username -> ใช้ WPA2-Enterprise
    WiFi.begin(cfg_ssid.c_str(), WPA2_AUTH_PEAP,
               cfg_user.c_str(), cfg_user.c_str(), cfg_pass.c_str());
  } else {
    // ไม่มี Username -> Wi-Fi บ้านทั่วไป
    WiFi.begin(cfg_ssid.c_str(), cfg_pass.c_str());
  }

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500); Serial.print("."); retry++;
  }
  return WiFi.status() == WL_CONNECTED;
}

void setup() {
  Serial.begin(115200);
  pinMode(RESET_BTN, INPUT_PULLUP);
  delay(500);

  // กดปุ่ม BOOT ค้างตอนเปิดเครื่อง = ล้างค่าแล้วเข้าโหมดตั้งค่า
  if (digitalRead(RESET_BTN) == LOW) {
    Serial.println("ล้างค่าที่บันทึกไว้...");
    prefs.begin("netcfg", false); prefs.clear(); prefs.end();
  }

  if (tryConnect()) {
    Serial.print("\n✅ เชื่อมต่อสำเร็จ IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nไม่มีค่า/เชื่อมไม่ได้ -> เข้าโหมดตั้งค่า");
    startConfigPortal();
  }
}

void loop() {
  // ทำงานเฉพาะตอนอยู่ในโหมดตั้งค่า
  if (WiFi.getMode() == WIFI_AP) {
    server.handleClient();
  }
}
```

## คำอธิบายโค้ด
- **Preferences (NVS)** คือพื้นที่หน่วยความจำถาวรของ ESP32 — เก็บค่าแบบ key/value คงอยู่แม้ปิดไฟ (เหมือน EEPROM แต่ใช้ง่ายกว่า)
- ตรรกะ Provisioning: ลองเชื่อมด้วยค่าที่บันทึกก่อน ถ้าไม่มี/ไม่ติด → เปิด AP ให้ตั้งค่า
- รองรับทั้ง Enterprise (มี Username) และ Wi-Fi บ้าน (ไม่มี Username) อัตโนมัติ
- ปุ่ม BOOT (GPIO0) ใช้ "Factory Reset" ค่าเครือข่าย สะดวกตอนติดตั้งหน้างาน
- **ความปลอดภัย**: รหัสไม่อยู่ในซอร์สโค้ดอีกต่อไป และอยู่ใน NVS ที่อ่านยากกว่าโค้ดที่ flash

## 🧪 โจทย์ท้าย Lab
1. เพิ่มหน้าแสดงสถานะ (`/status`) บอก IP, RSSI และ Uptime หลังเชื่อมต่อสำเร็จ
2. เพิ่ม dropdown ให้เลือก SSID จากผล `WiFi.scanNetworks()` แทนการพิมพ์เอง
3. คำถาม: ข้อดี-ข้อเสียของการเก็บรหัสใน NVS เทียบกับ Hardcode และเทียบกับการดึงจาก Server ส่วนกลาง?
