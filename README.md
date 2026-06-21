# Lab: การพัฒนาระบบด้วย Embedded System – Arduino

ชุดเนื้อหาฝึกอบรมเชิงปฏิบัติการ **2 วัน** โดย **AtSoftMaker** 🚀
ครอบคลุมส่วน **พื้นฐานภาษา C, เซ็นเซอร์พื้นฐาน, ระบบควบคุม (Control Systems), การสื่อสารอุตสาหกรรม (RS485/Modbus) และ ESP32 Gateway** สำหรับส่งข้อมูลเข้าสู่ OPS Server

---

## 🗺️ แผนผังหลักสูตร และโครงสร้างบทเรียน

หลักสูตรนี้ได้รับการปรับปรุงและจัดเก็บไฟล์เนื้อหาทั้งหมดไว้ในโครงการเดียวกัน โดยมีโครงสร้างหัวข้อเรียนรู้หลักดังนี้:

| ช่วงการอบรม | หัวข้อและเนื้อหาการเรียนรู้ | ลิงก์โฟลเดอร์เนื้อหาหลัก |
| :--- | :--- | :--- |
| **วันที่ 1 - ช่วงเช้า** | **พื้นฐานภาษา C/C++ สำหรับ Arduino** (ตัวแปร, การคำนวณ, เงื่อนไข, ลูป และฟังก์ชัน) | [Day1_C_Arduino_Lab](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab) |
| **วันที่ 1 - ช่วงเช้า** | **แล็ปการเขียนโปรแกรมเซ็นเซอร์พื้นฐาน (Arduino UNO)** (ดิจิทัล, อนาล็อก, บัซเซอร์, อุณหภูมิ, แสดงผล และวัดกระแส) | [Day1_Basic_Arduino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino) |
| **วันที่ 1 - ช่วงบ่าย** | **ระบบควบคุมและการสื่อสารอุตสาหกรรม (RS485/Modbus)** (Open/Closed Loop, PID, RS485 Master/Slave, Modbus RTU) | [Day1_Control_Communication](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication) |
| **วันที่ 2 - เต็มวัน** | **ESP32 Gateway & Cloud Connected Systems** (WiFi Enterprise, Config Portal, Modbus Gateway, Cloud Logging) | [Day2_ESP32_Gateway](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway) |

---

## 📂 รายละเอียดเนื้อหาในแต่ละบทเรียน (Syllabus Details)

### 1. [Day1_C_Arduino_Lab](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab) - พื้นฐานภาษา C/C++ สำหรับ Arduino
ไฟล์ซอร์สโค้ดในรูปแบบโครงการย่อยของ Arduino (`.ino`) เพื่อเรียนรู้พื้นฐานไวยากรณ์ภาษา C/C++ ที่จำเป็น:
* **Exercise 01:** [exercise01.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise01/exercise01.ino) - ชนิดตัวแปรต่างๆ (int, long, byte, float, double, char, String, bool) และการแสดงผลออก Serial
* **Exercise 02:** [exercise02.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise02/exercise02.ino) - โปรแกรมคำนวณแปลงหน่วยวินาทีเป็นรูปแบบ HH:MM:SS
* **Exercise 03:** [exercise03.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise03/exercise03.ino) - การตรวจสอบขนาดพื้นที่หน่วยความจำของข้อมูลด้วย `sizeof()`
* **Exercise 04:** [exercise04.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise04/exercise04.ino) - การแปลงข้อมูลแบบข้อความ (String) เป็นตัวเลขด้วย `toInt()` และ `toFloat()`
* **Exercise 05:** [exercise05.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise05/exercise05.ino) - ตัวอย่างการหารตัวเลขและหลักการทำงานของ Type Casting
* **Exercise 06:** [exercise06.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise06/exercise06.ino) - ลูกเล่นการจัดรูปแบบการปริ้นท์ (ฐาน 2, 8, 16 และจำนวนทศนิยม)
* **Exercise 07:** [exercise07.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise07/exercise07.ino) - ลอจิกเงื่อนไขควบคุมโครงสร้าง `if-else` และ `else-if`
* **Exercise 08:** [exercise08.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise08/exercise08.ino) - การเขียนเงื่อนไขร่วมกับตัวดำเนินการตรรกศาสตร์ OR (`||`)
* **Exercise 09:** [exercise09.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise09/exercise09.ino) - การทำตรรกะตรวจเช็คความปลอดภัยแบบประตูหนีไฟ (NOR Logic ด้วยตัวดำเนินการ `!`)
* **Exercise 10:** [exercise10.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise10/exercise10.ino) - การเปรียบเทียบการวนซ้ำระหว่างโครงสร้าง `for` loop และ `while` loop
* **Exercise 11:** [exercise11.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise11/exercise11.ino) - การสร้างโปรแกรมสูตรคูณตามที่ผู้ใช้กำหนดผ่านลูปทั้งสองรูปแบบ
* **Exercise 12:** [exercise12.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise12/exercise12.ino) - โปรแกรมคำนวณและประเมินเกณฑ์ดัชนีมวลกาย (BMI) โต้ตอบผ่าน Serial Monitor
* **Exercise 13:** [exercise13.ino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_C_Arduino_Lab/exercise13/exercise13.ino) - ฟังก์ชันรับอินพุตกว้างและยาวเพื่อคำนวณพื้นที่รูปสี่เหลี่ยมแบบ Dynamic

---

### 2. [Day1_Basic_Arduino](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino) - การต่อวงจรและเขียนโปรแกรมทำงานกับฮาร์ดแวร์พื้นฐาน (UNO)
รวบรวมใบงานปฏิบัติการ (Instruction) และโค้ดสำหรับเชื่อมต่อเซ็นเซอร์/อุปกรณ์แสดงผลยอดนิยม:
* **Lab 01:** [SW-420 Vibration Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab01%20SW-420/instruction.md) - การใช้งานเซ็นเซอร์วัดการสั่นสะเทือนแบบ Digital Input
* **Lab 02:** [SW-520D Tilt Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab02%20SW-520D/instruction.md) - เซ็นเซอร์ตรวจจับมุมก้ม/เงย และสวิตช์ลูกกลิ้งเอียงตัว
* **Lab 03:** [Obstacle Avoidance Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab03%20Obstacle%20Avoidance%20Sensor/instruction.md) - เซ็นเซอร์หลอดอินฟราเรดตรวจจับสิ่งกีดขวางระยะสั้น
* **Lab 04:** [Sound Detection Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab04%20Sound%20Detection%20Sensor/instruction.md) - การใช้งานเซ็นเซอร์ตรวจจับความดังเสียงและเคาะจังหวะ
* **Lab 05:** [Water Level Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab05%20Water%20Level%20Sensor/instruction.md) - การวัดระดับปริมาณน้ำสัมผัสแผ่นลายปริ้นท์แบบอนาล็อก
* **Lab 06:** [LDR Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab06%20LDR/instruction.md) - การรับค่าต้านทานแปรผันแสงสว่างเพื่อเขียนคำสั่งเปิด-ปิดไฟตามสภาวะมืด/สว่าง
* **Lab 07:** [RGB LED Module](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab07%20RGB%20LED%20Module/instruction.md) - แล็ปการหรี่และผสมสีด้วยสัญญาณ PWM ของหลอดไฟ LED 3 สี (R, G, B)
* **Lab 08:** [Active-Passive Buzzer](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab08%20Active-Passive%20Buzzer/instruction.md) - ศึกษาระบบเสียงไซเรนเตือนภัยและสร้างความถี่ตัวโน๊ตเพลง
* **Lab 09:** [DHT-21 Temperature/Humidity](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab09%20DHT-21/instruction.md) - อ่านค่าอุณหภูมิและความชื้นในอากาศจากเซ็นเซอร์ AM2301
* **Lab 10:** [DS18B20 Water Probe](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab10%20DS18B20/instruction.md) - การอ่านค่าอุณหภูมิของเหลวผ่านเซ็นเซอร์โปรโตคอลการสื่อสาร OneWire
* **Lab 11:** [GY-521-MPU6050 Accelerometer](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab11%20GY-521-MPU6050/instruction.md) - การอ่านค่าระดับมุมเอียงและความเร่ง 6 แกน ด้วยการสื่อสารแบบ I2C
* **Lab 12:** [LED Digital Tube 7-Segment](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab12%20LED%20Digital%20Tube/instruction.md) - แล็ปการควบคุมจอแสดงผล 7 Segment ชนิด 4 หลักเพื่อเขียนโปรแกรมแสดงผลนับเลขอัตโนมัติ
* **Lab 13:** [SCT-013 AC Current Sensor](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Basic_Arduino/Lab/Lab13%20SCT-013/instruction.md) - การต่อเซ็นเซอร์แคลมป์คล้องสายไฟกระแสสลับและคำนวณหากระแสโหลดไฟฟ้า

---

### 3. [Day1_Control_Communication](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication) - ระบบควบคุมอัตโนมัติและการสื่อสารเครือข่ายอุตสาหกรรม
บทเรียนที่เข้มข้นขึ้นเกี่ยวกับการควบคุมป้อนกลับ (Feedback Control) และการสื่อสารระยะไกลผ่านบัส RS485:
* **Lab 04:** [Relay Control](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab04_Relay_Control/instruction.md) - การควบคุมสวิตช์อิเล็กทรอนิกส์รีเลย์ขับโหลดไฟสูงอย่างปลอดภัย
* **Lab 05:** [Analog VR Control Line](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab05_Analog_VR_ControlLine/instruction.md) - การรับค่าแรงดันไฟฟ้า ADC แล้วเขียนเปรียบเทียบระดับช่วงควบคุม (Control Band)
* **Lab 05.1:** [Open Loop Control](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab05.1_Open_Loop_Control/instruction.md) - ระบบควบคุมแบบเปิดทำงานตามเวลา โดยไม่มีค่าเซ็นเซอร์มาประเมินผลลัพธ์
* **Lab 05.2:** [Closed Loop Control](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab05.2_Closed_Loop_Control/instruction.md) - ระบบควบคุมแบบป้อนกลับ ใช้ค่าเซ็นเซอร์เพื่อรักษาระดับจุดเป้าหมาย (Set Point)
* **Lab 05.3:** [PID Intro](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab05.3_PID_Intro/instruction.md) - การจำลองตัวควบคุมแบบ PID เบื้องต้นเพื่อหรี่กระแสควบคุมความร้อน/ความเร็วมอเตอร์อย่างราบเรียบ
* **Lab 06:** [RS485 Basic Transceiver](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab06_RS485_Basic/instruction.md) - การต่อไอซี MAX485 ส่งข้อความ String ข้ามบอร์ดไมโครคอนโทรลเลอร์
* **Lab 07:** [RS485 Master-Slave](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab07_RS485_Master_Slave/instruction.md) - การสร้างโปรโตคอลตกลงลำดับการส่งและดึงข้อมูลเพื่อไม่ให้สายส่งชนกัน
* **Lab 08:** [RS485 MultiDrop Network](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab08_RS485_MultiDrop/instruction.md) - แล็ปการเชื่อมต่ออุปกรณ์ Slave หลายตัวบนบัสส่งสัญญาณเส้นเดียว
* **Lab 09:** [Modbus RTU Slave Protocol](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day1_Control_Communication/Lab09_Modbus_RTU_Slave/instruction.md) - การเขียนโค้ดรองรับมาตรฐาน Modbus RTU ฝั่ง Slave ด้วย Mapping Registers (Holding/Input)

---

### 4. [Day2_ESP32_Gateway](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway) - ระบบไอโอทีเกตเวย์และคลาวด์คอนเนคทิวิตี (ESP32)
เน้นการพัฒนาโปรแกรมด้วยบอร์ด ESP32 เพื่อเชื่อมต่อผ่าน Wi-Fi และส่งต่อข้อมูลเซ็นเซอร์สู่เซิร์ฟเวอร์คลาวด์:
* **Lab 10:** [WiFi Basic Connection](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway/Lab10_WiFi_Basic/instruction.md) - การต่อเน็ต Wi-Fi แบบความปลอดภัยระดับทั่วไป (WPA/WPA2 Personal)
* **Lab 11:** [WPA2 Enterprise Network](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway/Lab11_WPA2_Enterprise/instruction.md) - การเขียนโปรแกรมต่อ Wi-Fi ในสำนักงานหรือสถานศึกษาที่ต้องการการระบุชื่อผู้ใช้ร่วม (802.1X PEAP)
* **Lab 12:** [WiFi Config Portal (AP Mode)](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway/Lab12_WiFi_Config_Portal/instruction.md) - สร้างหน้าเว็บเพจสำหรับกรอกรหัส Wi-Fi เพื่อบันทึกลงหน่วยความจำถาวร (Dynamic WiFi Provisioning)
* **Lab 13:** [ESP32 Gateway Modbus to RS485](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway/Lab13_ESP32_Gateway_RS485/instruction.md) - การเขียนโปรแกรมให้ ESP32 ทำหน้าที่เป็น Modbus Master เข้าไปอ่านค่าจาก Slave Node บนบัส RS485
* **Lab 14:** [Cloud HTTP Data Logging to OPS Server](file:///g:/My%20Drive/0.Working.2026/SSC20.%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9E%E0%B8%B1%E0%B8%92%E0%B8%99%E0%B8%B2Android/Lab_Embedded_System/Day2_ESP32_Gateway/Lab14_DataLogging_OPS/instruction.md) - แล็ปการแพ็ครวมชุดข้อมูลเซ็นเซอร์ในรูปแบบ JSON แล้วส่งผ่าน HTTP POST/API ไปลงบันทึกใน OPS Server แบบเรียลไทม์

---

## 🛠️ อุปกรณ์ที่ใช้และเครื่องมือเตรียมพร้อม (Hardware & Software Setup)

### 🔌 รายการอุปกรณ์ฮาร์ดแวร์หลัก (Hardware Requirements)
* **บอร์ดควบคุม:** Arduino UNO R3, Arduino MEGA 2560 (สำหรับเรียนรู้ RS485 / Multi-drop) และ ESP32 DevKit V1
* **โมดูลการเชื่อมต่อ:** ไอซีโมดูล MAX485 (สำหรับสื่อสาร RS485/Modbus)
* **ชุดเซ็นเซอร์พื้นฐาน:**
  - เซ็นเซอร์ตรวจจับการสั่นสะเทือน (SW-420), เซ็นเซอร์เอียง (SW-520D)
  - เซ็นเซอร์หลีกสิ่งกีดขวาง (Infrared Obstacle), เซ็นเซอร์เสียง (Sound)
  - เซ็นเซอร์วัดระดับน้ำ (Water Level), ตัวต้านทานไวแสง (LDR)
  - เซ็นเซอร์วัดอุณหภูมิและความชื้นสัมพัทธ์ในอากาศ (DHT-21 / AM2301)
  - เซ็นเซอร์วัดอุณหภูมิของเหลว (DS18B20 โพรบกันน้ำ)
  - เซ็นเซอร์มุมเอียงและค่าความเร่ง (GY-521 MPU6050)
  - เซ็นเซอร์วัดกระแสสลับ (SCT-013 AC Current Clamp)
* **ส่วนแสดงผลและเอาต์พุต:** รีเลย์ไฟสูง (Relay Module), หลอดไฟ RGB LED, บัซเซอร์ (Active/Passive), จอแสดงผล 7-Segment (LED Digital Tube)
* **อุปกรณ์เชื่อมต่อ:** Breadboard, ตัวต้านทาน 220Ω, 1kΩ, 10kΩ, ตัวต้านทานปรับค่าได้ (Potentiometer / VR) 10kΩ, สายเชื่อมต่อ Jumper Wires (M-M / M-F)

### 💻 เครื่องมือพัฒนาโปรแกรม (Software Prerequisites)
1. **Arduino IDE:** แนะนำให้ใช้เวอร์ชันล่าสุด (2.x ขึ้นไป) ดาวน์โหลดได้ที่ [Arduino Software](https://www.arduino.cc/en/software)
2. **ESP32 Core Package:** ค้นหาและติดตั้ง `esp32 by Espressif` ผ่านตัวจัดการบอร์ด (Boards Manager)
3. **USB Serial Driver:** ติดตั้งไดรเวอร์ `CH34x` ที่ให้มาในโฟลเดอร์โครงการเพื่อใช้เชื่อมต่อบอร์ด
4. **ไลบรารีภายนอกที่แนะนำให้ติดตั้งผ่าน Library Manager:**
   * `ModbusMaster` (สำหรับ Modbus Master Gateway)
   * `ArduinoModbus` หรือ `ModbusRTUSlave` (สำหรับ Modbus RTU Slave Node)
   * `DHT sensor library`
   * `OneWire` และ `DallasTemperature`
   * `Adafruit MPU6050`
   * `ArduinoJson` (สำหรับจัดการ Packet JSON ส่งคลาวด์)

---

## ⚠️ คำเตือนความปลอดภัย (Safety Information)
1. **ไฟฟ้ากระแสสลับแรงดันสูง (220V AC):** ในบทปฏิบัติการต่อชุดโมดูลรีเลย์ร่วมกับไฟฟ้าบ้าน 220V ให้ทำความเข้าใจคู่มืออย่างละเอียดและดำเนินการเชื่อมต่อวงจรภายใต้การดูแลของวิทยากรผู้เชี่ยวชาญเท่านั้น และตรวจสอบความถูกต้องก่อนเสียบปลั๊กไฟบ้านทุกครั้ง
2. **ระดับแรงดันไฟฟ้าของบอร์ด (Logic Levels):** บอร์ด Arduino UNO ทำงานที่ระดับลอจิก 5V ขณะที่บอร์ด ESP32 ทำงานที่ระดับลอจิก 3.3V การส่งสัญญาณสื่อสารหากันโดยตรงโดยไม่ใช้ชิปต้านทานหรือโมดูลสื่อสารกลาง (เช่น RS485) อาจทำให้อุปกรณ์ฝั่ง ESP32 เสียหายได้

---
**จัดทำโดย:** ห้างหุ้นส่วนจำกัด แอทซอฟท์เมกเกอร์ (AtSoftMaker) 👨‍💻
