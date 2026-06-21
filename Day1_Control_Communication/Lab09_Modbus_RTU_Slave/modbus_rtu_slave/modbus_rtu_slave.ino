// ============================================================
// Lab 09: Modbus RTU Slave บน Arduino UNO
// AtSoftMaker | Embedded System - Arduino
// ต้องติดตั้งไลบรารี: ModbusRTUSlave (by CMB27)
// ============================================================
#include <ModbusRTUSlave.h>
#include <SoftwareSerial.h>

const byte rxPin = 2;   // RO
const byte txPin = 3;   // DI
const byte dePin = 4;   // DE+RE
const byte ledPin = 7;
const byte sensorPin = A0;

const byte SLAVE_ID = 1;
const unsigned long BAUD = 9600;

SoftwareSerial mbSerial(rxPin, txPin);
ModbusRTUSlave modbus(mbSerial, dePin);

uint16_t holdingRegisters[3];   // Reg0=sensor, Reg1=LED, Reg2=counter

unsigned long lastTick = 0;
uint16_t counter = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  modbus.configureHoldingRegisters(holdingRegisters, 3);
  modbus.begin(SLAVE_ID, BAUD);
}

void loop() {
  holdingRegisters[0] = analogRead(sensorPin);

  if (millis() - lastTick >= 1000) {
    lastTick = millis();
    counter++;
    holdingRegisters[2] = counter;
  }

  modbus.poll();

  digitalWrite(ledPin, holdingRegisters[1] ? HIGH : LOW);
}
