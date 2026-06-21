// ============================================================
// Lab 21: RS485 Multi-drop - SLAVE NODE (Addressable)
// AtSoftMaker | Embedded System - Arduino
// ตั้ง MY_ADDRESS ให้ไม่ซ้ำกันในแต่ละบอร์ด
// ============================================================
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;
const int sensorPin = A0;

const int MY_ADDRESS = 1;   // Node1 = 1, Node2 = 2 ...

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
  digitalWrite(DE_RE, LOW);
  Serial.print("--- SLAVE Node #"); Serial.print(MY_ADDRESS); Serial.println(" ---");
}

void loop() {
  if (rs485.available()) {
    String frame = rs485.readStringUntil('\n');
    frame.trim();

    int sep = frame.indexOf(':');
    if (sep < 0) return;

    int targetAddr = frame.substring(0, sep).toInt();
    String cmd = frame.substring(sep + 1);

    if (targetAddr == MY_ADDRESS && cmd == "READ") {
      int val = analogRead(sensorPin);
      sendReply(String(MY_ADDRESS) + ":" + String(val));
    }
    // ไม่ใช่ Address เรา -> เงียบ
  }
}

