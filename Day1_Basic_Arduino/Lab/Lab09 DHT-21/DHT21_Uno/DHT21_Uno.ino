// Download Library: "DHT sensor library" และ "Adafruit Unified Sensor" จาก Library Manager
#include "DHT.h"
#define DHTPIN 2       // Data Wire to D2
#define DHTTYPE DHT21  // Config Model (DHT21)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" % \t Temp: "); 
  Serial.print(t); 
  Serial.println(" C");
  
  delay(1000); // หน่วงเวลา 1 วินาที
}
