#include "indLedControl.h"

#define IND_LED_PIN 3

#define TURN_IND_LED_ON   do{digitalWrite(IND_LED_PIN, HIGH);}while(0)
#define TURN_IND_LED_OFF  do{digitalWrite(IND_LED_PIN, LOW);}while(0)

void ILC_init(void)
{
  pinMode(IND_LED_PIN, OUTPUT);
  TURN_IND_LED_OFF;
}

void ILC_switchLed(uint8_t val)
{
  if(val)
  {
    TURN_IND_LED_OFF;
  }
  else
  {
    TURN_IND_LED_ON;
  }
}

void ILC_toggleLed(void)
{
   digitalWrite(IND_LED_PIN, !digitalRead(IND_LED_PIN));
}
