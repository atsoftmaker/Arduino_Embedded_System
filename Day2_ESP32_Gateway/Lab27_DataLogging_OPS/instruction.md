# Lab 27: Final Lab — Data Logging & Alert เข้า OPS Server (Realtime)

## Overview (ภาพรวม)
นี่คือ **Capstone** ที่รวมทุกอย่างเข้าด้วยกันเป็นระบบ End-to-End:

```
[UNO Node]  --RS485/Modbus-->  [ESP32 Gateway]  --Wi-Fi องค์กร-->  [OPS Server 10.5.15.5]
 (เซนเซอร์)                      (รวบรวม+ตัดสินใจ)                     (จัดเก็บ/แสดงผล)
```

ESP32 จะ (1) อ่านข้อมูลเซนเซอร์จาก Node ผ่าน Modbus (Lab 26) (2) ห่อข้อมูลเป็น **JSON Data Packet** (3) ส่งขึ้น OPS Server ผ่าน HTTP POST แบบ **เรียลไทม์** และ (4) ตรวจเงื่อนไข ถ้าค่าผิดปกติให้ส่ง **Alert** พิเศษ

นี่คือสถาปัตยกรรม IIoT (Industrial IoT) จริงที่ใช้เก็บข้อมูลหน้างานเข้าสู่ระบบส่วนกลาง

## ไลบรารีที่ต้องติดตั้ง
- **ModbusMaster** (Doc Walker)
- **ArduinoJson** (โดย Benoit Blanchon)
- `WiFi.h`, `HTTPClient.h` (มากับ ESP32 Core)

## ค่าที่ต้องตั้ง (จากข้อมูลลูกค้า)
- **OPS Server:** `http://10.5.15.5` (พอร์ต/endpoint ตามที่ฝ่าย IT กำหนด ตัวอย่างใช้ `/api/data`)
- **Wi-Fi:** TBV-WiFi (WPA2-Enterprise) — ในงานจริงดึงค่าจาก Config Portal (Lab 25)
- **เกณฑ์ Alert:** ตัวอย่างตั้ง sensor > 800 = ผิดปกติ

## Hardware Wiring
เหมือน Lab 26 ทุกประการ (ESP32 + MAX485 ↔ UNO Node บนบัส RS485)

## Code (รวมระบบ End-to-End)
```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ModbusMaster.h>

// ---------- Wi-Fi (Enterprise) ----------
const char* ssid     = "TBV-WiFi";
const char* identity = "DOMAIN\\username";
const char* username = "DOMAIN\\username";
const char* password = "YOUR_AD_PASSWORD";

// ---------- OPS Server ----------
const char* OPS_URL   = "http://10.5.15.5/api/data";
const char* OPS_ALERT = "http://10.5.15.5/api/alert";
const char* DEVICE_ID = "GW-LINE-A-01";

// ---------- Modbus ----------
#define RX2 16
#define TX2 17
#define DE_RE 4
#define SLAVE_ID 1
ModbusMaster node;
void preTx()  { digitalWrite(DE_RE, HIGH); }
void postTx() { digitalWrite(DE_RE, LOW); }

// ---------- เกณฑ์ Alert ----------
const uint16_t SENSOR_LIMIT = 800;

unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 5000;   // ส่งทุก 5 วินาที

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, WPA2_AUTH_PEAP, identity, username, password);
  Serial.print("เชื่อมต่อ Wi-Fi องค์กร");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 60) { delay(500); Serial.print("."); retry++; }
  Serial.println(WiFi.status() == WL_CONNECTED ?
                 "\nOnline IP: " + WiFi.localIP().toString() : "\nWi-Fi ล้มเหลว");
}

// ส่ง HTTP POST เป็น JSON ไปยัง URL ที่กำหนด
bool postJson(const char* url, String payload) {
  if (WiFi.status() != WL_CONNECTED) return false;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST(payload);
  Serial.print("POST "); Serial.print(url);
  Serial.print(" -> HTTP "); Serial.println(code);
  http.end();
  return (code > 0 && code < 400);
}

void setup() {
  Serial.begin(115200);
  pinMode(DE_RE, OUTPUT); digitalWrite(DE_RE, LOW);

  Serial2.begin(9600, SERIAL_8N1, RX2, TX2);
  node.begin(SLAVE_ID, Serial2);
  node.preTransmission(preTx);
  node.postTransmission(postTx);

  connectWiFi();
  Serial.println("--- Lab 27: Data Logging to OPS Server ---");
}

void loop() {
  if (millis() - lastSend < SEND_INTERVAL) return;
  lastSend = millis();

  // 1) อ่านข้อมูลจาก Node ผ่าน Modbus
  uint8_t result = node.readHoldingRegisters(0, 3);
  if (result != node.ku8MBSuccess) {
    Serial.print("อ่าน Node ไม่สำเร็จ 0x"); Serial.println(result, HEX);
    return;
  }
  uint16_t sensor  = node.getResponseBuffer(0);
  uint16_t ledStat = node.getResponseBuffer(1);
  uint16_t counter = node.getResponseBuffer(2);

  // 2) สร้าง JSON Data Packet
  StaticJsonDocument<256> doc;
  doc["device_id"] = DEVICE_ID;
  doc["sensor"]    = sensor;
  doc["led"]       = ledStat;
  doc["counter"]   = counter;
  doc["rssi"]      = WiFi.RSSI();
  doc["uptime_s"]  = millis() / 1000;
  String payload;
  serializeJson(doc, payload);

  // 3) ส่งข้อมูลปกติเข้า OPS Server
  postJson(OPS_URL, payload);

  // 4) ตรวจเงื่อนไข Alert
  if (sensor > SENSOR_LIMIT) {
    StaticJsonDocument<256> alert;
    alert["device_id"] = DEVICE_ID;
    alert["level"]     = "WARNING";
    alert["message"]   = "Sensor เกินเกณฑ์";
    alert["value"]     = sensor;
    alert["limit"]     = SENSOR_LIMIT;
    String aPayload;
    serializeJson(alert, aPayload);
    postJson(OPS_ALERT, aPayload);
    Serial.println("⚠️ ส่ง ALERT แล้ว!");
  }
}
```

## ตัวอย่าง JSON ที่ส่งขึ้น OPS Server
```json
{
  "device_id": "GW-LINE-A-01",
  "sensor": 742,
  "led": 0,
  "counter": 153,
  "rssi": -58,
  "uptime_s": 765
}
```

## คำอธิบายโค้ด
- **ArduinoJson** ประกอบ payload เป็น JSON มาตรฐานที่ฝั่ง Server parse ได้ทุกภาษา
- แยก endpoint ข้อมูลปกติ (`/api/data`) ออกจาก Alert (`/api/alert`) ทำให้ฝั่ง OPS จัดลำดับความสำคัญได้
- ส่งแบบ Non-blocking ด้วย `millis()` ทุก 5 วินาที (ปรับได้) ไม่บล็อกการอ่าน Modbus
- มี `device_id` เพื่อให้ Server แยกแยะว่ามาจาก Gateway ตัวไหน/ไลน์ผลิตใด
- งานจริงควรเพิ่ม retry/queue เก็บข้อมูลตอนเน็ตหลุด และใช้ HTTPS ถ้า Server รองรับ

## ✅ Checklist ทดสอบ End-to-End (ใช้ตอนนำเสนอ Project)
1. UNO Node (Lab 22) รันอยู่ และ VR ปรับค่าได้
2. ESP32 Gateway อ่านค่าจาก Node ผ่าน Modbus ได้ (เห็นใน Serial)
3. ESP32 เชื่อม TBV-WiFi ได้ (มี IP)
4. OPS Server (10.5.15.5) ได้รับ HTTP POST (ตรวจ log ฝั่ง Server หรือใช้ mock server)
5. หมุน VR จนเกิน 800 → เห็น Alert ถูกส่ง

## 🧪 โจทย์ท้าย Lab / ต่อยอด
1. เพิ่มกลไก buffer เก็บข้อมูลลง NVS เมื่อ Wi-Fi หลุด แล้วส่งย้อนหลังเมื่อกลับมาออนไลน์
2. เพิ่ม timestamp จริงด้วย NTP (`configTime`) ให้ข้อมูลมีเวลาแม่นยำ
3. คำถาม: ถ้า OPS Server ล่ม Gateway ควรทำอย่างไรเพื่อไม่ให้ข้อมูลสูญหาย? ออกแบบกลยุทธ์ store-and-forward

