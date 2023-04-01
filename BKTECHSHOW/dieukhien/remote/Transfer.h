#include "PS2X_lib.h"  //for v1.6

#define ps2_dat  9
#define ps2_cmd 5
#define ps2_sel 10
#define ps2_clk 6 
#define pre false
#define rum false
int error = 0; 
byte type = 0;
byte vibrate = 0;
  float data[20];
PS2X ps2x;
class Transfer{
  public:
  void Check_error();
  void Read_data();
};
void Transfer::Check_error()
{
  error = ps2x.config_gamepad(ps2_clk,ps2_cmd,ps2_sel,ps2_dat, pre, rum); 
  if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
}
void Transfer::Read_data()
{
  data[0] = 111;
  data[1] = ps2x.Button(PSB_PAD_UP);
  data[2] = ps2x.Button(PSB_PAD_DOWN);
  data[3] = ps2x.Button(PSB_PAD_RIGHT);
  data[4] = ps2x.Button(PSB_PAD_LEFT);
  data[5] = ps2x.Analog(PSS_LY);
  data[6] = ps2x.Analog(PSS_LX);
}
