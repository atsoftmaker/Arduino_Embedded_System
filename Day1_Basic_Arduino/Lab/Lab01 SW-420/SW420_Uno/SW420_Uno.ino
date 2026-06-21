int vibPin = 2; // D0 from module to D2 from board

void setup() {
  Serial.begin(9600);
  pinMode(vibPin, INPUT);
}

void loop() {
  int val = digitalRead(vibPin);
  
  if (val == 0) {
    Serial.println("ไม่สั่น");
  } else {
    Serial.println("สั่น!!"); 
  }
  
  delay(100);
}
