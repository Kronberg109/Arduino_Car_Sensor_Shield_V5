//Setup Servo
#include<Servo.h>
Servo servo;

//Define Motors
const int LeftMotorForward = 5;
const int LeftMotorBackward = 4;
const int RightMotorForward = 3;
const int RightMotorBackward = 2;

//Define Sensor
const int trig = 6;
const int echo = 7;

//Sensor Variables
float duration_us, distance_cm;
int obst;
int obstacle;
const int threshold = 20;

//Servo Variables
int rot_modif = 0;

void setup(){

  //Debug
  Serial.begin(9600);

  //Setting Pins
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //Setting Servo
  servo.attach(11);
  servo.write(90);
  
}

void loop(){

  obst = checkStraight();
  if (obst == 0){
    driveStraight();
  }
  else{
    obst = checkLeft();
    if(obst == 0){
      turnLeft();
    }
    else{
      obst = checkRight();
      if(obst == 0){
        turnRight();
      }
    }
  }
    
}

void driveStraight(){
  
    //Left Motor Forward
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    
    //Right Motor Forward
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
     
}

void turnRight(){

    //Sensor Forward
    servo.write(90);

    //Left Motor Forward
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    
    //Right Motor Backward
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, HIGH);

    //Rotate Until Nothing Is In Front + 100 ms
    while(obstacle == 1){
      obstacle = sensDistance();
    }

    delay(50);
     
}

void turnLeft(){

    //Sensor Forward
    servo.write(90);

    //Left Motor Backward
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, HIGH);

    //Right Motor Forward
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);

    //Rotate Until Nothing Is In Front + 100 ms
    while(obstacle == 1){
      obstacle = sensDistance();
    }
    
    delay(50);
     
}

int checkStraight(){
  
  //Turn Servo/Sensor
  servo.write(60 + rot_modif);
  delay(250);

  //Higher FOV
  rot_modif += 30;
  if(rot_modif > 60){
    rot_modif = 0;
  }

  //Use Sensor
  obst = sensDistance();
  return obst;
}

int checkRight(){
  
  //Turn Servo/Sensor
  servo.write(180);
  delay(250);

  //Use Sensor
  obst = sensDistance();
  return obst;
}

int checkLeft(){
  
  //Turn Servo/Sensor
  servo.write(0);
  delay(100);

  //Use Sensor
  obst = sensDistance();
  return obst;
}

int sensDistance(){

  //Send Out Pulse
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  //Read Return
  duration_us = pulseIn(echo,HIGH);
  distance_cm = 0.017 * duration_us;

  //Debug
  Serial.println(distance_cm);

  //Check If Obstacle Is Close And Return
  if(distance_cm > threshold){
    return 0;  
  }
  else{
    return 1;
  }
  
}
