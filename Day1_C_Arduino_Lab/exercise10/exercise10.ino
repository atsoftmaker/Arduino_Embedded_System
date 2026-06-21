
void setup() {
  Serial.begin(9600);
 
  Serial.println("--- For Loop ---");
  // เริ่มที่ 3, ทำตราบใดที่ i มากกว่า 0, ลดค่าทีละ 1
  for (int i = 3; i > 0; i--) { 
    Serial.println(i);
  }
 
  Serial.println("--- While Loop ---");
  int count = 3;
  while (count > 0) {
    Serial.println(count);
    count--; 
  }
  Serial.println("Go!");
}
void loop() {}

