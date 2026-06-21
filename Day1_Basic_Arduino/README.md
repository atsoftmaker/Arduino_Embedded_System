#  Arduino UNO Programming Lab

## รายละเอียดโครงการ (Overview)
ที่เก็บรวบรวมแลปและผลการทดลองการเขียนโปรแกรมบนบอร์ด **Arduino UNO** เพื่อเรียนรู้การทำงานร่วมกับเซ็นเซอร์ และอุปกรณ์ควบคุมต่างๆ โดยมุ่งเน้นการประยุกต์ใช้งานแบบเบื้องต้น

## วัตถุประสงค์ (Objectives)
- เพื่อศึกษาการรับส่งข้อมูลผ่านพอร์ต Digital และ Analog
- เพื่อฝึกฝนการเขียนโปรแกรมควบคุมอุปกรณ์ Hardware ด้วยภาษา C++ (Arduino)
- เพื่อสร้างคลังความรู้เกี่ยวกับแนวทางการต่อวงจร (Wiring) และการแก้ปัญหาในแลป

## อุปกรณ์หลักที่ใช้ (Core Hardware)
1. **Microcontroller:** Arduino UNO R3
2. **Breadboard:** 400 / 830 Points
3. **Connectivity:** USB Type-B Cable
4. **Other:** Jumper Wires (M-M, M-F), Resistors 1-10kΩ

##  หมายเหตุ (Note)

หากไม่สามารถอัปโหลดโค้ดลงบอร์ด ให้ติดตั้ง Driver_CH34X ที่แนบไป

## โครงสร้างแลป (List of Experiments)
ใน Repository นี้จะประกอบไปด้วยแลปต่างๆ ดังนี้:

* **Lab 01:** [SW-420 Vibration Sensor](./Lab/Lab01%20SW-420/instruction.md) - การใช้เซ็นเซอร์ตรวจจับแรงสั่นสะเทือน
* **Lab 02:** [SW-520D Tilt Sensor](./Lab/Lab02%20SW-520D/instruction.md) - การใช้งานเซ็นเซอร์วัดการเอียง
* **Lab 03:** [Obstacle Avoidance Sensor](./Lab/Lab03%20Obstacle%20Avoidance%20Sensor/instruction.md) - การใช้เซ็นเซอร์อินฟราเรดตรวจจับสิ่งกีดขวาง
* **Lab 04:** [Sound Detection Sensor](./Lab/Lab04%20Sound%20Detection%20Sensor/instruction.md) - การอ่านค่าอนาล็อกจากเซ็นเซอร์ตรวจจับเสียง
* **Lab 05:** [Water Level Sensor](./Lab/Lab05%20Water%20Level%20Sensor/instruction.md) - การใช้งานเซ็นเซอร์วัดระดับน้ำ
* **Lab 06:** [LDR](./Lab/Lab06%20LDR/instruction.md) - การใช้เซ็นเซอร์วัดแสงเพื่อแยกแยะความสว่าง/มืด
* **Lab 07:** [RGB LED Module](./Lab/Lab07%20RGB%20LED%20Module/instruction.md) - การควบคุมโมดูลหลอดไฟ LED 3 สีและการผสมสี
* **Lab 08:** [Active-Passive Buzzer](./Lab/Lab08%20Active-Passive%20Buzzer/instruction.md) - การสร้างเสียงด้วย Active และ Passive Buzzer
* **Lab 09:** [DHT-21](./Lab/Lab09%20DHT-21/instruction.md) - การวัดอุณหภูมิและความชื้นสัมพัทธ์
* **Lab 10:** [DS18B20](./Lab/Lab10%20DS18B20/instruction.md) - การวัดอุณหภูมิน้ำด้วยโพรบกันน้ำผ่านโปรโตคอล 1-Wire
* **Lab 11:** [GY-521-MPU6050](./Lab/Lab11%20GY-521-MPU6050/instruction.md) - การวัดความเร่งและไจโรสโคปผ่าน I2C
* **Lab 12:** [LED Digital Tube](./Lab/Lab12%20LED%20Digital%20Tube/instruction.md) - การแสดงผลตัวเลขด้วยจอ 7-Segment
* **Lab 13:** [SCT-013](./Lab/Lab13%20SCT-013/instruction.md) - เซ็นเซอร์วัดกระแสไฟฟ้าสลับ (AC Current Sensor)

---
**จัดทำโดย:** [AtSoftMaker]