// ============================================================
// Lab 13: ESP32 Modbus Gateway (Master) อ่านข้อมูลจาก UNO Node
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: ESP32 Dev Module | ไลบรารี: ModbusMaster (Doc Walker)
// ============================================================
#include <ModbusMaster.h>

#define RX2 16
#define TX2 17
#define DE_RE 4
#define MODBUS_BAUD 9600
#define SLAVE_ID 1

ModbusMaster node;

void preTransmission()  { digitalWrite(DE_RE, HIGH); }
void postTransmission() { digitalWrite(DE_RE, LOW); }

void setup() {
  Serial.begin(115200);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);

  Serial2.begin(MODBUS_BAUD, SERIAL_8N1, RX2, TX2);

  node.begin(SLAVE_ID, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  Serial.println("--- Lab 13: ESP32 Modbus Gateway ---");
}

void loop() {
  uint8_t result = node.readHoldingRegisters(0, 3);

  if (result == node.ku8MBSuccess) {
    uint16_t sensor  = node.getResponseBuffer(0);
    uint16_t ledStat = node.getResponseBuffer(1);
    uint16_t counter = node.getResponseBuffer(2);

    Serial.println("อ่านข้อมูลจาก Node สำเร็จ");
    Serial.print("  Sensor : "); Serial.println(sensor);
    Serial.print("  LED    : "); Serial.println(ledStat);
    Serial.print("  Counter: "); Serial.println(counter);
  } else {
    Serial.print("อ่านไม่สำเร็จ (Modbus error 0x");
    Serial.print(result, HEX); Serial.println(")");
  }

  delay(2000);
}
