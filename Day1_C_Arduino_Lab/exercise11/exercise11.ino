void setup() {
  Serial.begin(9600);
  int mae = 2; // กำหนดแม่ที่ต้องการ
  
  Serial.print("--- แม่ ");
  Serial.print(mae);
  Serial.println(" Loop ---");
    
  for (int i = 1; i <= 12; i++) {
    Serial.print(mae);
    Serial.print(" x ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(mae * i);
  }
  Serial.print("--- แม่ ");
  Serial.print(mae);
  Serial.println(" While---");

  // กำหนดค่าเริ่มต้น While loop
  int i = 1; 

  while (i <= 12) { 
    Serial.print(mae);
    Serial.print(" x ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(mae * i);
    i++; 
  }
}


void loop() {
}

