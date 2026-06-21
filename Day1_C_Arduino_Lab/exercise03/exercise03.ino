void setup() {
  Serial.begin(9600);
  
  boolean myBool = true;
  char myChar = 'A';
  int myInt = 32000;
  long myLong = 1000000;
  float myFloat = 3.14;

  Serial.println("--- สำรวจขนาดหน่วยความจำ (Bytes) ---");
  
  Serial.print("1. boolean กินพื้นที่: "); 
  Serial.println(sizeof(myBool));
  
  Serial.print("2. char กินพื้นที่: "); 
  Serial.println(sizeof(myChar));
  
  Serial.print("3. int กินพื้นที่: "); 
  Serial.println(sizeof(myInt));
  
  Serial.print("4. long กินพื้นที่: "); 
  Serial.println(sizeof(myLong));
  
  Serial.print("5. float กินพื้นที่: "); 
  Serial.println(sizeof(myFloat));
}

void loop() {}

