// ============================================================
// Lab 20: RS485 Master/Slave Command - SLAVE
// AtSoftMaker | Embedded System - Arduino
// ============================================================
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;
const int ledPin = 7;
const int sensorPin = A0;

void sendReply(String msg) {
  digitalWrite(DE_RE, HIGH); delay(2);
  rs485.println(msg);
  rs485.flush();
  digitalWrite(DE_RE, LOW);
}

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- SLAVE ---");
}

void loop() {
  if (rs485.available()) {
    String cmd = rs485.readStringUntil('\n');
    cmd.trim();
    Serial.print("รับคำสั่ง: "); Serial.println(cmd);

    if (cmd == "READ") {
      int val = analogRead(sensorPin);
      sendReply(String(val));
    } else if (cmd == "LED:ON") {
      digitalWrite(ledPin, HIGH);
      sendReply("ACK:LED_ON");
    } else if (cmd == "LED:OFF") {
      digitalWrite(ledPin, LOW);
      sendReply("ACK:LED_OFF");
    } else {
      sendReply("ERR:UNKNOWN");
    }
  }
}

