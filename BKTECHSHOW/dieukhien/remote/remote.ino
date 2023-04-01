#include "Transfer.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8

Transfer trans;
const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);

void setup(){
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(pipe);
  trans.Check_error();
}

void loop(){
  trans.Read_data();
  radio.write( data, sizeof(data) );
 
 error = ps2x.config_gamepad(ps2_clk,ps2_cmd,ps2_sel,ps2_dat, pre, rum);  
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2){ //Guitar Hero Controller
   
   ps2x.read_gamepad();          //read controller 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on                                            //how hard you press the blue (X) button    
    delay(50);   
}
}
