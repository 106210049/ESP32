#include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>
 #include <Servo.h>     
   Servo servo_gap;
   Servo servo_khop;          

 #define CE_PIN 7
 #define CSN_PIN 8
      int servo1Pin = 9;
      int servo2Pin = 10;
      int enbA = A1;
      int in1 = 4;       
      int in2 = 5;        
      int in3 = 6;        
      int in4 = 3;  
      int enbB = A2 ; 
      int servoPos1 , servoPos2;
bool ng1, ng2 , ng3 , ng4 ; int  ng5, ng6;

 
 
 const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);
     float data[10];
 void setup()
 {
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(in3, OUTPUT);
        pinMode(in4, OUTPUT);
        pinMode(enbA, OUTPUT);
        pinMode(enbB, OUTPUT);

   servo_gap.attach(servo1Pin); 
   servo_khop.attach(servo2Pin); 
   
 Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1,pipe);
    radio.startListening();

 }
 void loop(){
if (radio.available())
      {
    radio.read( data, sizeof(data) );
    
      
 if(data[0] == 111)
      {
         ng1 = data[1];
        Serial.println(ng1);
         ng2 = data[2];
        Serial.println(ng2);
         ng3 = data[3];
        Serial.println(ng3);
         ng4 = data[4];
        Serial.println(ng4);
         ng5 = data[5];
        Serial.println(ng5);
         ng6 = data[6];
        Serial.println(ng6);
      }
      
       
       
      }
      if(ng1 == 1 ) 
       {
           dithang(150);
       }
       else if(ng2 == 1 )
       {
           dilui(200);
        }
       else if(ng3 == 1)
       {
           disangtrai(200);
        }
       else if(ng4 == 1)
       {
           disangphai(200);
        }
       else
       {
           dunglai();
        }
       
  servoPos1= map(ng5, 0, 255, 0, 180);
       servo_gap.write(servoPos1);
       servoPos2= map(ng6, 0, 255, 0, 180);
       servo_khop.write(servoPos2);
 }

 
 void dithang(int tocdo)
{
  analogWrite(enbA, tocdo);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);


}
void dunglai(){
  analogWrite(enbA, 0);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  }

void disangphai(int tocdo)
{
  analogWrite(enbA, tocdo);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);


}
void disangtrai(int tocdo)
{
  analogWrite(enbA, 0);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);

}

void dilui(int tocdo)
{
  analogWrite(enbA, tocdo);
  analogWrite(enbB, tocdo);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);

}
