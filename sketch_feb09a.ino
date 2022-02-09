#include<Servo.h>
Servo myservo;

void setup() {
  myservo.attach(1);
  myservo.write(90);

}

void loop() {
  myservo.write(0);
  delay(50);
  myservo.write(180);

}
