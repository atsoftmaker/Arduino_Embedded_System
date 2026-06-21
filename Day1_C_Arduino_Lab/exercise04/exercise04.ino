void setup() {
  Serial.begin(9600);
  
  // จำลองข้อมูลที่รับมาจากอินเทอร์เน็ตเป็น String
  String rawData1 = "125";
  String rawData2 = "36.75";
  
  // แปลง String เป็น Integer (จำนวนเต็ม)
  int parsedInt = rawData1.toInt();
  
  // แปลง String เป็น Float (ทศนิยม)
  float parsedFloat = rawData2.toFloat();
  
  Serial.println("--- ทดสอบการแปลงข้อความเป็นตัวเลข ---");
  
  Serial.print("ข้อมูลดิบ 1 (String): "); 
  Serial.println(rawData1);
  Serial.print("แปลงเป็น Int แล้วลองบวก 10: "); 
  Serial.println(parsedInt + 10); // ถ้าแปลงสำเร็จ ค่าจะต้องเป็น 135

  Serial.println("- - - - - - - - - - -");

  Serial.print("ข้อมูลดิบ 2 (String): "); 
  Serial.println(rawData2);
  Serial.print("แปลงเป็น Float แล้วลองบวก 1.5: "); 
  Serial.println(parsedFloat + 1.5); // ถ้าแปลงสำเร็จ ค่าจะต้องเป็น 38.25
}

void loop() {}

