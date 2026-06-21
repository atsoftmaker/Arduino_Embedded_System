void setup() {
  Serial.begin(9600);
  
  int colorCode = 255;
  float myPi = 3.14159265;

  Serial.println("--- ลูกเล่นการแสดงผล (Print Formatting) ---");
  
  // 1. การแสดงเลขฐานต่างๆ ของตัวแปร int
  Serial.println("[ ทดสอบเลขฐาน ]");
  Serial.print("แบบฐานสิบ (DEC): "); Serial.println(colorCode, DEC); // 255
  Serial.print("แบบฐานสิบหก (HEX): "); Serial.println(colorCode, HEX); // FF
  Serial.print("แบบฐานสอง (BIN): "); Serial.println(colorCode, BIN); // 11111111
  
  Serial.println("");

  // 2. การกำหนดจุดทศนิยมของตัวแปร float
  Serial.println("[ ทดสอบจุดทศนิยม ]");
  Serial.print("ปริ้นแบบปกติ (Default): "); Serial.println(myPi); // ปกติจะได้ 2 ตำแหน่ง
  Serial.print("ปริ้น 1 ตำแหน่ง: "); Serial.println(myPi, 1);
  Serial.print("ปริ้น 4 ตำแหน่ง: "); Serial.println(myPi, 4);
  Serial.print("ปริ้น 6 ตำแหน่ง: "); Serial.println(myPi, 6);
}

void loop() {}

