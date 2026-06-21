// ============================================================
// Lab 05.2: Closed Loop Control - On/Off + Hysteresis
// AtSoftMaker | Embedded System - Arduino
// ============================================================

const int sensorPin = A0;   // จำลองเซนเซอร์ด้วย VR
const int relayPin  = 8;
const int ledGreen  = 6;
const int ledRed    = 7;

const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

const float SET_POINT  = 50.0;
const float HYSTERESIS = 3.0;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);
  Serial.println("--- Lab 05.2: Closed Loop (On/Off) Control ---");
}

void loop() {
  int raw = analogRead(sensorPin);
  float processValue = map(raw, 0, 1023, 0, 100);
  float error = SET_POINT - processValue;

  if (processValue < SET_POINT - HYSTERESIS) {
    digitalWrite(relayPin, RELAY_ON);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  } else if (processValue > SET_POINT + HYSTERESIS) {
    digitalWrite(relayPin, RELAY_OFF);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
  } else {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  Serial.print("SetPoint: "); Serial.print(SET_POINT);
  Serial.print(" | Current: "); Serial.print(processValue);
  Serial.print(" | Error: "); Serial.println(error);

  delay(300);
}
