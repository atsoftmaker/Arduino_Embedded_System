// ============================================================
// Lab 16: Open Loop Control - สั่งงานตามเวลา (Non-blocking)
// AtSoftMaker | Embedded System - Arduino
// ============================================================

const int relayPin = 8;
const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

const unsigned long ON_DURATION  = 5000;   // ทำงาน 5 วินาที
const unsigned long OFF_DURATION = 10000;  // พัก 10 วินาที

unsigned long previousMillis = 0;
bool pumpState = false;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);
  Serial.println("--- Lab 16: Open Loop Control ---");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long interval = pumpState ? ON_DURATION : OFF_DURATION;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    pumpState = !pumpState;

    if (pumpState) {
      digitalWrite(relayPin, RELAY_ON);
      Serial.println(">> ปั๊มทำงาน (ON) ตามเวลาที่ตั้งไว้");
    } else {
      digitalWrite(relayPin, RELAY_OFF);
      Serial.println(">> ปั๊มหยุด (OFF) รอรอบถัดไป");
    }
  }
}

