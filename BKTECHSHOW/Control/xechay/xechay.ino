
#include "Run.h"     
const uint64_t pipe = 0xE8E8F0F0E1LL;
Car car;
RF24 radio(CE_PIN, CSN_PIN);
 void setup()
 {
   car.Setup();
   
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
//        Serial.println(ng1);
         ng2 = data[2];
//        Serial.println(ng2);
         ng3 = data[3];
//        Serial.println(ng3);
         ng4 = data[4];
//        Serial.println(ng4);
         ng5 = data[5];
//        Serial.println(ng5);
         ng6 = data[6];
//        Serial.println(ng6);
    }
    if(ng1 == 1 ) 
       {
           car.dithang(150);
       }
       else if(ng2 == 1 )
       {
           car.dilui(200);
        }
       else if(ng3 == 1)
       {
           car.disangtrai(200);
        }
       else if(ng4 == 1)
       {
           car.disangphai(200);
        }
       else
       {
           car.dunglai();
       }
       servoPos1= map(ng5, 0, 255, 0, 180);
       servo_gap.write(servoPos1);
       servoPos2= map(ng6, 0, 255, 0, 180);
       servo_khop.write(servoPos2);
  }
}
