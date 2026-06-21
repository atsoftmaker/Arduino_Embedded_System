// ลำดับขาที่ต่อ: a, b, c, d, e, f, g
int segments[] = {2, 3, 8, 7, 6, 5, 4}; 

// รูปแบบเลข 0-9 สำหรับ Common Cathode
byte data[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    showDigit(i);
    delay(1000); // หน่วงเวลา 1 วินาทีเปลี่ยนเลข
  }
}

void showDigit(int n) {
  for (int i = 0; i < 7; i++) {
    // ใช้ bitRead เพื่ออ่านค่าแต่ละบิตจากขวาไปซ้าย (เริ่มจาก a)
    digitalWrite(segments[i], bitRead(data[n], i));
  }
}
