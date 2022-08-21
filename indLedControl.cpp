#include "indLedControl.h"

#define IND_LED_PIN 3

#define TURN_IND_LED_ON   while(0){digitalWrite(IND_LED_PIN, HIGH)}
#define TURN_IND_LED_OFF   while(0){digitalWrite(IND_LED_PIN, LOW)}

void ILC_init(void)
{
  pinMode(IND_LED_PIN, OUTPUT);
}
