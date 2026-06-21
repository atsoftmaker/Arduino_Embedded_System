// ============================================================
// Lab 27: ESP32 Gateway -> OPS Server (Data Logging + Alert)
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: ESP32 Dev Module
// ไลบรารี: ModbusMaster, ArduinoJson
// ============================================================
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

const uint16_t SENSOR_LIMIT = 800;

unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 5000;

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, WPA2_AUTH_PEAP, identity, username, password);
  Serial.print("เชื่อมต่อ Wi-Fi องค์กร");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 60) { delay(500); Serial.print("."); retry++; }
  Serial.println(WiFi.status() == WL_CONNECTED ?
                 "\nOnline IP: " + WiFi.localIP().toString() : "\nWi-Fi ล้มเหลว");
}

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

  uint8_t result = node.readHoldingRegisters(0, 3);
  if (result != node.ku8MBSuccess) {
    Serial.print("อ่าน Node ไม่สำเร็จ 0x"); Serial.println(result, HEX);
    return;
  }
  uint16_t sensor  = node.getResponseBuffer(0);
  uint16_t ledStat = node.getResponseBuffer(1);
  uint16_t counter = node.getResponseBuffer(2);

  StaticJsonDocument<256> doc;
  doc["device_id"] = DEVICE_ID;
  doc["sensor"]    = sensor;
  doc["led"]       = ledStat;
  doc["counter"]   = counter;
  doc["rssi"]      = WiFi.RSSI();
  doc["uptime_s"]  = millis() / 1000;
  String payload;
  serializeJson(doc, payload);

  postJson(OPS_URL, payload);

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
    Serial.println("ส่ง ALERT แล้ว!");
  }
}

