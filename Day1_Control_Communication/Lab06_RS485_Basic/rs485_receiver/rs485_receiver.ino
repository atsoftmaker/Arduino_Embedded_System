// ============================================================
// Lab 06: RS485 Basic - RECEIVER (Board B)
// AtSoftMaker | Embedded System - Arduino
// ============================================================
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3); // RX=D2, TX=D3
const int DE_RE = 4;

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);   // คงโหมดรับไว้ตลอด
  Serial.println("--- Board B: RS485 Receiver ---");
}

void loop() {
  if (rs485.available()) {
    String msg = rs485.readStringUntil('\n');
    Serial.print("รับได้: ");
    Serial.println(msg);
  }
}
