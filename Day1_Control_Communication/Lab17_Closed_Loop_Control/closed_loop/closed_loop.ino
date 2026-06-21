// ============================================================
// Lab 17: Closed Loop Control - On/Off + Hysteresis
// AtSoftMaker | Embedded System - Arduino
// ============================================================

const int sensorPin = A0;   // จำลองเซนเซอร์ด้วย VR
const int relayPin  = 8;
const int ledGreen  = 6;
const int ledRed    = 7;

const int RELAY_ON  = HIGH;
const int RELAY_OFF = LOW;

const float SET_POINT  = 50.0;
const float HYSTERESIS = 3.0;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(relayPin, RELAY_OFF);
  Serial.println("--- Lab 17: Closed Loop (On/Off) Control ---");
}

void loop() {
  int raw = analogRead(sensorPin);
  float processValue = map(raw, 0, 1023, 0, 100);
  float error = SET_POINT - processValue;
  int stage =0;

  if (processValue < SET_POINT - HYSTERESIS) {
    digitalWrite(relayPin, RELAY_ON);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    stage=1;
  } else if (processValue > SET_POINT + HYSTERESIS) {
    digitalWrite(relayPin, RELAY_OFF);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    stage=2;
  } else {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    stage=3;
  }

  Serial.print("SetPoint: "); Serial.print(SET_POINT);
  Serial.print(" | Current: "); Serial.print(processValue);
  Serial.print(" | Error: "); Serial.print(error);
  Serial.print(" | ST: ");
  if( stage==1){
    Serial.println("ทำงาน");
  }else if(stage==2){
    Serial.println("หยุด");
  }else if(stage==3){
    Serial.println("อยู่ในเป้าหมาย");
  }

  delay(300);
}

