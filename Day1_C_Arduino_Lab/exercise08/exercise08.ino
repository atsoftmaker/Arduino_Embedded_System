void setup() {
  Serial.begin(9600);
  int temp = 38;

  if (temp < 20 || temp > 35) { // ใช้ || สำหรับเงื่อนไข "อย่างใดอย่างหนึ่ง"
    Serial.println("Danger: Air conditioner needed!");
  } else {
    Serial.println("Temperature OK");
  }
}
void loop() {}

