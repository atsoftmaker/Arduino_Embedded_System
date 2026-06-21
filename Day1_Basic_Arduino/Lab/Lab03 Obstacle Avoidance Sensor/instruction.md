# Arduino IR Obstacle Sensor (Obstacle Avoidance Sensor)

## Overview (ภาพรวม)
แลปนี้เป็นการทดลองใช้งาน `**IR Obstacle Avoidance Sensor (เซ็นเซอร์อินฟราเรดตรวจจับสิ่งกีดขวาง)**` หลักการทำงานคือตัวโมดูลจะยิงแสงอินฟราเรดออกไป หากมีวัตถุมาขวาง แสงจะสะท้อนกลับมาเข้าตัวรับสัญญาณ 

ในแลปนี้ บอร์ด Arduino จะอ่านค่าจากขา OUT ของเซ็นเซอร์ โดยโมดูลนี้ทำงานแบบ **Active LOW** หมายความว่าปกติจะส่งค่า `1` (HIGH) แต่เมื่อตรวจพบสิ่งกีดขวางในระยะ จะส่งค่า `0` (LOW) ออกมาแทน เหมาะสำหรับนำไปใช้ทำหุ่นยนต์หลบหลีกสิ่งกีดขวาง, ระบบนับจำนวนสิ่งของบนสายพาน หรือสมาร์ทคาร์ชั่วคราว

## Hardware Wiring (การต่อวงจร)
การเชื่อมต่อสายสัญญาณระหว่างโมดูล IR Sensor และบอร์ด Arduino UNO สามารถทำได้ตามตารางนี้:

| IR Obstacle Sensor | Arduino UNO Board |
| :--- | :--- |
| **VCC** | 5V (หรือ 3.3V) |
| **GND** | GND |
| **OUT** (Digital Output) | **D2** (Digital Pin 2) |

![Circuit](../Images/c03.png)

## Code
อัปโหลดโค้ดด้านล่างนี้ลงในบอร์ด Arduino (ตั้งค่า Baud Rate ใน Serial Monitor เป็น `9600`):

```cpp
int irPin = 2; // OUT from module to D2 from board

void setup() {
  Serial.begin(9600);
  pinMode(irPin, INPUT);
}

void loop() {
  int val = digitalRead(irPin);
  
  if ( val == 0 ) {
    Serial.println("มีสิ่งกีดขวาง");
  } else {
    Serial.println("ไม่มีสิ่งกีดขวาง");
  }
  
  delay(100);
}
```

Output:

![Output](../Images/o03.png)