// ============================================================
// Lab 25: ESP32 Web Config Portal (Dynamic Provisioning + NVS)
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: ESP32 Dev Module
// ============================================================
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

WebServer server(80);
Preferences prefs;

const char* AP_SSID = "ESP32-Setup";
const char* AP_PASS = "12345678";
const int   RESET_BTN = 0;   // ปุ่ม BOOT

String cfg_ssid, cfg_user, cfg_pass;

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

  prefs.begin("netcfg", false);
  prefs.putString("ssid", cfg_ssid);
  prefs.putString("user", cfg_user);
  prefs.putString("pass", cfg_pass);
  prefs.end();

  server.send(200, "text/html", "<h3>บันทึกแล้ว กำลังรีบูตเพื่อเชื่อมต่อ...</h3>");
  delay(1500);
  ESP.restart();
}

void startConfigPortal() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.print("เข้าโหมดตั้งค่า | ต่อ Wi-Fi '"); Serial.print(AP_SSID);
  Serial.print("' แล้วเปิด http://"); Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.begin();
}

bool tryConnect() {
  prefs.begin("netcfg", true);
  cfg_ssid = prefs.getString("ssid", "");
  cfg_user = prefs.getString("user", "");
  cfg_pass = prefs.getString("pass", "");
  prefs.end();

  if (cfg_ssid == "") return false;

  WiFi.mode(WIFI_STA);
  if (cfg_user != "") {
    WiFi.begin(cfg_ssid.c_str(), WPA2_AUTH_PEAP,
               cfg_user.c_str(), cfg_user.c_str(), cfg_pass.c_str());
  } else {
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

  if (digitalRead(RESET_BTN) == LOW) {
    Serial.println("ล้างค่าที่บันทึกไว้...");
    prefs.begin("netcfg", false); prefs.clear(); prefs.end();
  }

  if (tryConnect()) {
    Serial.print("\nเชื่อมต่อสำเร็จ IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nไม่มีค่า/เชื่อมไม่ได้ -> เข้าโหมดตั้งค่า");
    startConfigPortal();
  }
}

void loop() {
  if (WiFi.getMode() == WIFI_AP) {
    server.handleClient();
  }
}

