void setup() {
  Serial.begin(9600);
  bool isDoorOpen = false;   // ประตูไม่ได้เปิด
  bool isWindowOpen = true;  // หน้าต่างเปิด

  Serial.println("--- Security Lock System ---");
  
  // NOR Logic: ไม่ใช่ทั้ง (ประตูเปิด หรือ หน้าต่างเปิด)
  if ( !(isDoorOpen || isWindowOpen) ) {
    Serial.println("System: ALL LOCKED. Safe to leave. ");
  } else {
    Serial.println("System: WARNING! Cannot lock. Check doors/windows. ");
  }
}

void loop() {}

