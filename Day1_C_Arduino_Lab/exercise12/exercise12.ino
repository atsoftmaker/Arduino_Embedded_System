// 1. ฟังก์ชันคำนวณเลข BMI (เหมือนเดิมที่คุณเขียน)
float calculateBMI(float weight, float height) {
  float bmi = weight / (height * height);
  return bmi; 
}

// 2. ฟังก์ชันวิเคราะห์ผล (เหมือนเดิมที่คุณเขียน)
void printHealthStatus(float bmiValue) {
  Serial.print("ค่า BMI ของคุณคือ: ");
  Serial.println(bmiValue);
  
  if (bmiValue < 18.5) {
    Serial.println("สถานะ: น้ำหนักน้อยเกินไป");
  } else if (bmiValue >= 18.5 && bmiValue <= 24.9) {
    Serial.println("สถานะ: น้ำหนักปกติ (สุขภาพดี)");
  } else {
    Serial.println("สถานะ: น้ำหนักเกิน/อ้วน");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("--- โปรแกรมคำนวณ BMI แบบโต้ตอบ ---");
}

void loop() {
  float myWeight, myHeight_cm, myHeight_m;

  // --- รับค่าน้ำหนัก ---
  Serial.println("กรุณาพิมพ์ 'น้ำหนัก' (kg) แล้วกด Enter:");
  while (Serial.available() == 0) {
    // โปรแกรมจะ "หยุดรอ" ตรงนี้จนกว่าจะมีคนพิมพ์ส่งมา (เหมือน input() ใน Python)
  }
  myWeight = Serial.parseFloat(); // อ่านค่าตัวเลขที่ส่งมา
  Serial.print("> น้ำหนักที่คุณใส่: "); Serial.println(myWeight);
  
  // ล้างค่าค้างในระบบ (Flush buffer)
  while(Serial.available() > 0) { Serial.read(); }

  // --- รับค่าส่วนสูง ---
  Serial.println("กรุณาพิมพ์ 'ส่วนสูง' (cm) แล้วกด Enter:");
  while (Serial.available() == 0) {
    // หยุดรออีกครั้ง
  }
  myHeight_cm = Serial.parseFloat(); 
  myHeight_m = myHeight_cm / 100.0; // แปลง cm เป็น m เพื่อเข้าสูตร
  Serial.print("> ส่วนสูงที่คุณใส่: "); Serial.print(myHeight_cm); Serial.println(" cm");

  Serial.println("---------------------------");

  // --- เรียกใช้ฟังก์ชันที่คุณสร้างไว้ ---
  float result = calculateBMI(myWeight, myHeight_m);
  printHealthStatus(result);

  Serial.println("--- จบการทำงาน ---");
  while (true) {
	// โปรแกรมจะติดในรูปนี้จนกว่าจะ reset
  }
  
}

