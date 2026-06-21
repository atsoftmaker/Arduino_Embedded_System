// ============================================================
// Lab 08: RS485 Multi-drop - MASTER (Round-robin Poll)
// AtSoftMaker | Embedded System - Arduino
// ============================================================
#include <SoftwareSerial.h>
SoftwareSerial rs485(2, 3);
const int DE_RE = 4;
const int NODE_LIST[] = {1, 2};
const int NODE_COUNT = 2;

void sendCommand(String cmd) {
  digitalWrite(DE_RE, HIGH); delay(2);
  rs485.println(cmd);
  rs485.flush();
  digitalWrite(DE_RE, LOW);
}

String readReply(unsigned long timeout = 400) {
  unsigned long start = millis();
  while (millis() - start < timeout) {
    if (rs485.available()) return rs485.readStringUntil('\n');
  }
  return "TIMEOUT";
}

void setup() {
  Serial.begin(9600);
  rs485.begin(9600);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW);
  Serial.println("--- MASTER (Multi-drop Poll) ---");
}

void loop() {
  for (int i = 0; i < NODE_COUNT; i++) {
    int addr = NODE_LIST[i];
    sendCommand(String(addr) + ":READ");

    String reply = readReply();
    reply.trim();
    Serial.print("Node "); Serial.print(addr);
    Serial.print(" -> "); Serial.println(reply);

    delay(500);
  }
  Serial.println("------------------");
  delay(1000);
}
