// ActiveBuzzer.ino
int buzzerPin = 2; // + from module to D2 from board

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Make Noise (HIGH)
  digitalWrite(buzzerPin, HIGH); 
  delay(1000); 
  
  // Silence (LOW)
  digitalWrite(buzzerPin, LOW);  
  delay(1000);
}

