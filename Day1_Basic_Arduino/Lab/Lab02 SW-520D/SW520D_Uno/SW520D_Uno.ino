int tiltPin = 2; // D0 from module to D2 from board

void setup() {
  Serial.begin(9600);
  pinMode(tiltPin, INPUT);
}

void loop() {
  int val = digitalRead(tiltPin);
  Serial.println(val); // แสดงค่า 0 หรือ 1 ตามการเอียง
  delay(100);
}
