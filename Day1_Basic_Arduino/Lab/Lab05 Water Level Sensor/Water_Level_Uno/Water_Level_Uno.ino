int waterPin = A0; // A0 from module to A0 from board

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(waterPin);
  
  if (val < 10) {
    Serial.println("แห้ง");
  } 
  else if (val >= 10 && val <= 300) {
    Serial.println("ชื้นเล็กน้อย");
  } 
  else if (val > 300 && val <= 600) {
    Serial.println("ชื้นมาก");
  } 
  else {
    Serial.println("เปียก");
  }

  delay(1000); 
}
