// ============================================================
// Lab 05: Analog Input (VR) -> Control Line
// AtSoftMaker | Embedded System - Arduino
// บอร์ด: Arduino UNO / MEGA
// ============================================================

const int vrPin  = A0;   // Potentiometer (VR)
const int ledPin = 9;    // LED ขา PWM (~)

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("--- Lab 05: Analog VR -> Control Line ---");
}

void loop() {
  int rawValue    = analogRead(vrPin);              // 0 - 1023
  int controlLine = map(rawValue, 0, 1023, 0, 255); // PWM 0 - 255
  int percent     = map(rawValue, 0, 1023, 0, 100); // 0 - 100 %

  analogWrite(ledPin, controlLine);

  Serial.print("Raw: ");          Serial.print(rawValue);
  Serial.print("  | Control: ");  Serial.print(controlLine);
  Serial.print("  | Power: ");    Serial.print(percent);
  Serial.println(" %");

  delay(200);
}
