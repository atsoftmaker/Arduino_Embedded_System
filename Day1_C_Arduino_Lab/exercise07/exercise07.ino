void setup() {
  Serial.begin(9600);
  int score = 75;
  
  Serial.print("Score: ");
  Serial.println(score);

  if (score >= 80) {
    Serial.println("Grade: A");
  } else if (score >= 70 && score < 80) { // ต้องเชื่อมด้วย && (และ)
    Serial.println("Grade: B");
  } else {
    Serial.println("Grade: C");
  }
}
void loop() {}

