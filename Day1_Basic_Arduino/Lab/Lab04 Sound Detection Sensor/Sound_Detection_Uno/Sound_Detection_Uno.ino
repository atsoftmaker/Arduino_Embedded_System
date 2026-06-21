int soundPin = A0; 

void setup() {
  Serial.begin(9600);
  pinMode(soundPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(soundPin);
  Serial.println(sensorValue);
  delay(10);  
}
