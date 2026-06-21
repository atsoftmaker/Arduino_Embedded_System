int ldrPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(ldrPin);
  Serial.println(val)
  if (val > 600) {
    Serial.println("มืด");
  } else {
    Serial.println("สว่าง");
  }
  
  delay(500);
}
