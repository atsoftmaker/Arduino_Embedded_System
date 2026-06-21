#include <Wire.h>
#include <math.h>

const int MPU_addr = 0x68;

// Set Offset (Calibration)
float roll_offset = 0.0;   

// Variables for Low-Pass Filter
float filtered_roll = 0;
const float alpha = 0.15; // Adjust smoothness (lower value = smoother)

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // Wake up MPU
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  
  // ขออ่านข้อมูล 6 ไบต์ต่อเนื่อง (X, Y, Z แกนละ 2 ไบต์)
  Wire.requestFrom(MPU_addr, 6, true); 
  
  // อ่านค่ามาทีละแกน (นำไบต์สูงมาต่อกับไบต์ต่ำ) แล้วหารด้วย 16384.0 เพื่อแปลงเป็นสเกล g
  float AcX = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  float AcY = (Wire.read() << 8 | Wire.read()) / 16384.0; 
  float AcZ = (Wire.read() << 8 | Wire.read()) / 16384.0; 

  Serial.print("X: "); 
  Serial.print(AcX); 
  Serial.print(" | Y: "); 
  Serial.print(AcY); 
  Serial.print(" | Z: "); 
  Serial.println(AcZ); 

  delay(100); 
}
