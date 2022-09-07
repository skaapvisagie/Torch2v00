#include "trigger.h"
#include "indLedControl.h"
#include "batStatus.h"
#include "init.h"
#include "adc.h"
#include "timers.h"

//#define DEBUG
#ifdef DEBUG
  #include <SoftwareSerial.h>
  #define RX    6   // *** D3, Pin 6 PWM  Green
  #define TX    7   // *** D4, Pin 7 BT   Yellow
#endif

void setup() 
{
  INIT_init();

  #ifdef DUBUG
    SoftwareSerial Serial(RX, TX);
    Serial.begin(57600);
    Serial.println("init");
  #endif   
}

void loop() 
{
	Timers_UpdateTimers();
  // if(TRIGGER_triggerFound())
    // ILC_toggleLed();
//
//  if(ADC_getBatVoltage() >= 500)
//  {
//    ILC_toggleLed();
//  }
  //Serial.println(ADC_getBatVoltage());
  //delay(500);
}
