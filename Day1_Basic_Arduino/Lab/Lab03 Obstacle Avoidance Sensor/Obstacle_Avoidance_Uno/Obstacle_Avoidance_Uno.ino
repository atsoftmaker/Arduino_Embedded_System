int irPin = 2; // OUT from module to D2 from board

void setup() {
  Serial.begin(9600);
  pinMode(irPin, INPUT);
}

void loop() {
  int val = digitalRead(irPin);
  
  if ( val == 0 ) {
    Serial.println("มีสิ่งกีดขวาง");
  } else {
    Serial.println("ไม่มีสิ่งกีดขวาง");
  }
  
  delay(100);
}
