#include<Arduino.h>
const int ledPin=16;
const int ledStates=LOW; // Status of led

hw_timer_t *timer=NULL; // Set up timer
portMUX_TYPE timerMux= portMUX_INITIALIZER_UNLOCKED; // It can avoid conflicts while the programe is compiling

// timer function
void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);// vào chế độ tránh xung đột
  digitalWrite(ledPin,~ledStates); // đảo giá trị led
  portEXIT_CRITICAL_ISR(&timerMux); // thoát
}

void setup()
{
  Serial.begin(9600);

  // Set up GPIO led pin is output
  pinMode(ledPin,OUTPUT);
  // set up timer with cycles= 1us because quartz of ESP run with 8MHz
  timer= timerBegin(0,80,true);
  // set up timer function for timer
  timerAttachInterrupt(timer,&onTimer,true);
  // set up time for timer is 1s
  timerAlarmWrite(timer,1000000,true);
  // begin running timer
  timerAlarmEnable(timer);
}

void loop()
{
  // do nothing
}