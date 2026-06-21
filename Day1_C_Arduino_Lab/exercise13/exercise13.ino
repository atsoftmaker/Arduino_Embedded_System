// 1. ฟังก์ชันคำนวณพื้นที่ (รับค่า int คืนค่า long เพื่อรองรับพื้นที่ขนาดใหญ่)
long calculateArea(int width, int length) {
  long area = (long)width * length;
  return area;
}

void setup() {
  Serial.begin(9600);
  Serial.println("--- โปรแกรมคำนวณพื้นที่สี่เหลี่ยม ---");
}

void loop() {
  int w, l;

  // --- รับค่าความกว้าง ---
  Serial.println("ป้อน 'ความกว้าง' (หน่วยเต็ม):");
  while (Serial.available() == 0) {} // ยืนรอ input
  w = Serial.parseInt();           // อ่านค่าเป็นจำนวนเต็ม (int)
  Serial.print("> กว้าง: "); Serial.println(w);
  
  while(Serial.available() > 0) { Serial.read(); } // ล้าง Buffer

  // --- รับค่าความยาว ---
  Serial.println("ป้อน 'ความยาว' (หน่วยเต็ม):");
  while (Serial.available() == 0) {} // ยืนรอ input
  l = Serial.parseInt();           // อ่านค่าเป็นจำนวนเต็ม (int)
  Serial.print("> ยาว: "); Serial.println(l);

  // --- คำนวณและแสดงผล ---
  long totalArea = calculateArea(w, l);
  
  Serial.println("---------------------------");
  Serial.print("พื้นที่สี่เหลี่ยมคือ: ");
  Serial.print(totalArea);
  Serial.println(" ตารางหน่วย");
  Serial.println("---------------------------\n");
  Serial.println("จบการทำงาน");
  while (true) {
  }
}

