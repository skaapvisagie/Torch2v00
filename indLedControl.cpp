#include "indLedControl.h"

#define IND_LED_PIN PB3

#define TURN_IND_LED_ON   do{PORTB |= (1 << IND_LED_PIN);}while(0)
#define TURN_IND_LED_OFF  do{PORTB &= ~(1 << IND_LED_PIN);}while(0)
#define TOGGLE_IND_LED    do{PORTB ^= (1 << IND_LED_PIN);}while(0)

void ILC_init(void)
{
  DDRB |= (1 << PB3);
  TURN_IND_LED_OFF;
}

void ILC_indicateLowBatt(void)
{
	
}

void ILC_indicateDeadBatt(void)
{
	
}

void ILC_switchLed(uint8_t val)
{
  if(val)
    TURN_IND_LED_OFF;
  else
    TURN_IND_LED_ON;
}

void ILC_toggleLed(void)
{
  TOGGLE_IND_LED;
}

