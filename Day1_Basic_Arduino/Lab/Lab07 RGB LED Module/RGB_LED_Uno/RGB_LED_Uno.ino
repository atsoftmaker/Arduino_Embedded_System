//  R, G, B are PWM
int redPin = 2; // R from module to D2 from board
int greenPin = 3; // G from module to D2 from board
int bluePin = 4;  // B from module to D2 from board

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // เทสต์สีแดง
  analogWrite(redPin, 255); analogWrite(greenPin, 0); analogWrite(bluePin, 0);
  delay(1000);
  // เทสต์สีเขียว
  analogWrite(redPin, 0); analogWrite(greenPin, 255); analogWrite(bluePin, 0);
  delay(1000);
  // เทสต์สีน้ำเงิน
  analogWrite(redPin, 0); analogWrite(greenPin, 0); analogWrite(bluePin, 255);
  delay(1000);
}
