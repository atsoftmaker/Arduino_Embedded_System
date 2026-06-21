// ============================================================
// Lab 19: RS485 Basic - SENDER (Board A)
// AtSoftMaker | Embedded System - Arduino
// ============================================================
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3); // RX=D2, TX=D3
const int DE_RE = 4;

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- Board A: RS485 Sender ---");
}

void loop() {
  digitalWrite(DE_RE, HIGH);   // โหมดส่ง
  delay(2);
  rs485.println("HELLO from Board A");
  rs485.flush();
  digitalWrite(DE_RE, LOW);    // กลับมาโหมดรับ

  Serial.println("ส่ง: HELLO from Board A");
  delay(1000);
}

