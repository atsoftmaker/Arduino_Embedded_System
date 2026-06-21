// Download Library: OneWire, DallasTemperature From Library Manager
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 // ต่อขา Data สีเหลือง เข้า Pin 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); // สั่งให้เซ็นเซอร์เตรียมอ่านค่าอุณหภูมิ
  float tempC = sensors.getTempCByIndex(0); // ดึงค่าอุณหภูมิตัวที่ 0 (ตัวแรก)
  
  Serial.print("Water Temp: ");
  Serial.print(tempC);
  Serial.println(" C");
  
  delay(1000); // หน่วงเวลา 1 วินาที
}
