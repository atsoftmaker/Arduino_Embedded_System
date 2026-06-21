// ============================================================
// Lab 23: ESP32 Wi-Fi Basic (Station Mode)
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: ESP32 Dev Module
// ============================================================
#include <WiFi.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.print("กำลังเชื่อมต่อ Wi-Fi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nเชื่อมต่อสำเร็จ!");
    Serial.print("IP Address: "); Serial.println(WiFi.localIP());
    Serial.print("Signal (RSSI): "); Serial.print(WiFi.RSSI()); Serial.println(" dBm");
  } else {
    Serial.println("\nเชื่อมต่อไม่สำเร็จ ตรวจสอบ SSID/Password");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Online | IP: "); Serial.print(WiFi.localIP());
    Serial.print(" | RSSI: "); Serial.println(WiFi.RSSI());
  } else {
    Serial.println("Offline - กำลังเชื่อมต่อใหม่...");
    WiFi.reconnect();
  }
  delay(5000);
}

