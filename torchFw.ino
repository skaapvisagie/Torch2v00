#include "trigger.h"
#include "indLedControl.h"
#include "batStatus.h"
#include "init.h"

void setup() 
{
  INIT_init();
}

void loop() 
{
  //ILC_switchLed((uint8_t)TRIGGER_triggerFound());
  if(TRIGGER_triggerFound())
    ILC_toggleLed();
    
  delay(500);
}
