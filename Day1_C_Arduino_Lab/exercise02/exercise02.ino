void setup() {
  Serial.begin(9600);
  
  // สมมติเซนเซอร์จับเวลาทำงานมาได้ 10,000 วินาที
  unsigned long totalSeconds = 10000; 
  
  // คำนวณหา ชั่วโมง, นาที, และวินาทีที่เหลือ
  int hours = totalSeconds / 3600;          // 1 ชั่วโมง = 3600 วินาที
  int remainingAfterHours = totalSeconds % 3600; // เศษที่เหลือจากชั่วโมง
  
  int minutes = remainingAfterHours / 60;   // เอาเศษมาหา นาที
  int seconds = remainingAfterHours % 60;   // เศษสุดท้ายคือ วินาที
  
  Serial.println("--- System Uptime ---");
  Serial.print("Total Seconds: ");
  Serial.println(totalSeconds);
  
  Serial.print("Format (HH:MM:SS) -> ");
  Serial.print(hours); Serial.print("h : ");
  Serial.print(minutes); Serial.print("m : ");
  Serial.print(seconds); Serial.println("s");
}

void loop() {}

