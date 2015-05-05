#include <Servo.h>

#define HeadHolderCenter 1450 
#define HeadRotateCenter 1415
#define LmaxHRC 2000
#define RmaxHRC 


Servo HeadHolder;
Servo HeadRotate;


  void setup() {
    Serial.begin(57600);
    HeadHolder.attach(6);
    HeadRotate.attach(7);
  }

  void loop() {
    while(!Serial.available());
    char ch = (char) Serial.read();
    switch (ch) {
      case '1': 
      HeadRotate.writeMicroseconds(1700);
      Serial.println("right");
      break;
      case '2': 
      HeadRotate.writeMicroseconds(800);
      Serial.println("left");
      break;
      default:
      Serial.println("Invalid option");
    }
  }