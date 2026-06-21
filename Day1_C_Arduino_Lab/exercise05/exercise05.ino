void setup() {
  Serial.begin(9600);
  
  int numA = 10;
  int numB = 3;
  
  // วิธีที่ 1: หารกันตรงๆ แล้วเก็บลง float
  float result1 = numA / numB; 
  
  // วิธีที่ 2: บังคับให้คอมพิวเตอร์มอง numA และ numB เป็น float ชั่วคราวก่อนหาร
  float result2 = (float)numA / (float)numB;
  
  Serial.println("--- การหารตัวเลข (Type Casting) ---");
  
  Serial.print("โจทย์: 10 หาร 3 (เก็บผลลัพธ์แบบ Float)\n");
  
  Serial.print("ผลลัพธ์แบบที่ 1 (ไม่ Cast): "); 
  Serial.println(result1); // จะได้ 3.00 (ทศนิยมหายไประหว่างทาง)
  
  Serial.print("ผลลัพธ์แบบที่ 2 (Cast แล้ว): "); 
  Serial.println(result2); // จะได้ 3.33 (ได้ค่าที่แม่นยำ)
}

void loop() {}

