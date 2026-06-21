// ============================================================
// Lab 20: RS485 Master/Slave Command - MASTER
// AtSoftMaker | Embedded System - Arduino
// ============================================================
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;

void sendCommand(String cmd) {
  digitalWrite(DE_RE, HIGH); delay(2);
  rs485.println(cmd);
  rs485.flush();
  digitalWrite(DE_RE, LOW);
}

String readReply(unsigned long timeout = 500) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (rs485.available()) {
      return rs485.readStringUntil('\n');
    }
  }
  return "TIMEOUT";
}

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- MASTER ---");
}

void loop() {
  sendCommand("READ");
  Serial.print("Sensor = "); Serial.println(readReply());
  delay(1000);

  sendCommand("LED:ON");
  Serial.print("Reply  = "); Serial.println(readReply());
  delay(1000);

  sendCommand("LED:OFF");
  Serial.print("Reply  = "); Serial.println(readReply());
  delay(1000);
}

