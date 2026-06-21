// ============================================================
// Lab 18: PID Control เบื้องต้น (เขียนเอง ไม่ใช้ไลบรารี)
// AtSoftMaker | Embedded System - Arduino
// ============================================================

const int sensorPin = A0;
const int outputPin = 9;   // PWM

float setPoint = 50.0;     // เป้าหมาย (0-100)

float Kp = 4.0;
float Ki = 0.2;
float Kd = 1.0;

float integral = 0;
float lastError = 0;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  lastTime = millis();
  Serial.println("--- Lab 18: PID Control ---");
}

void loop() {
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  if (dt <= 0) dt = 0.001;

  int raw = analogRead(sensorPin);
  float pv = map(raw, 0, 1023, 0, 100);
  float error = setPoint - pv;

  float P = Kp * error;
  integral += error * dt;
  float I = Ki * integral;
  float derivative = (error - lastError) / dt;
  float D = Kd * derivative;

  float output = P + I + D;
  output = constrain(output, 0, 255);
  integral = constrain(integral, -500, 500);  // anti-windup

  analogWrite(outputPin, (int)output);

  lastError = error;
  lastTime = now;

  Serial.print("SP:"); Serial.print(setPoint);
  Serial.print(" PV:"); Serial.print(pv);
  Serial.print(" Err:"); Serial.print(error);
  Serial.print(" Out:"); Serial.println(output);

  delay(50);
}

