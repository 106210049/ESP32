
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define CE_PIN 7
#define CSN_PIN 8
Servo servo_gap;
Servo servo_khop;
int servo1Pin = 9;
int servo2Pin = 10;
int enbA = A1;
int in1 = 4;       
int in2 = 5;        
int in3 = 6;        
int in4 = 3;  
int enbB = A2 ; 
int servoPos1 , servoPos2;
float data[10];
bool ng1, ng2 , ng3 , ng4 ; 
int  ng5, ng6;

class Car{
  public:
  void Setup();
  void dithang(int a);
  void dilui(int a);
  void dunglai();
  void disangphai(int a);
  void disangtrai(int a);
};

void Car::Setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  servo_gap.attach(servo1Pin); 
  servo_khop.attach(servo2Pin); 
}

 void Car::dithang(int tocdo)
{
  analogWrite(enbA, tocdo);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void Car::dunglai(){
  analogWrite(enbA, 0);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void Car::disangphai(int tocdo)
{
  analogWrite(enbA, tocdo);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void Car::disangtrai(int tocdo)
{
  analogWrite(enbA, 0);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);

}

void Car::dilui(int tocdo)
{
  analogWrite(enbA, tocdo);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
