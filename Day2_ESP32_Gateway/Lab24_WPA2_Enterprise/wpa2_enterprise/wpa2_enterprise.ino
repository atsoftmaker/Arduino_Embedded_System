// ============================================================
// Lab 24: ESP32 WPA2-Enterprise (TBV-WiFi / Windows Login)
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: ESP32 Dev Module | Core 3.x
// ============================================================
#include <WiFi.h>

const char* ssid     = "TBV-WiFi";
const char* identity = "DOMAIN\\username";   // บัญชี Windows/AD
const char* username = "DOMAIN\\username";
const char* password = "YOUR_AD_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n--- Lab 24: WPA2-Enterprise ---");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);

  // ESP32 core 3.x overload
  WiFi.begin(ssid, WPA2_AUTH_PEAP, identity, username, password);

  Serial.print("กำลังเข้าสู่เครือข่ายองค์กร");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 60) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nเข้าเครือข่ายองค์กรสำเร็จ");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
    Serial.print("MAC: "); Serial.println(WiFi.macAddress());
  } else {
    Serial.println("\nล็อกอินไม่สำเร็จ ตรวจสอบ Username/Password หรือสิทธิ์บัญชี");
  }
}

void loop() {
  Serial.println(WiFi.status() == WL_CONNECTED ? "Online" : "Offline");
  delay(5000);
}

