// ============================================================
// Lab 27: Digital Output - Relay Control (220V Load)
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: Arduino UNO / MEGA
// ============================================================

const int relayPin = 8;

// Relay Module ส่วนใหญ่เป็น Active LOW (LOW = ON)
// หากโมดูลของคุณเป็น Active HIGH ให้สลับสองค่านี้
const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);   // ปิดไว้ก่อนเพื่อความปลอดภัย
  Serial.println("--- Lab 27: Relay Control ---");
}

void loop() {
  Serial.println("สั่ง Relay: ON (โหลดทำงาน)");
  digitalWrite(relayPin, RELAY_ON);
  delay(3000);

  Serial.println("สั่ง Relay: OFF (ตัดโหลด)");
  digitalWrite(relayPin, RELAY_OFF);
  delay(3000);
}

