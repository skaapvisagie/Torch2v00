#include "indLedControl.h"
#include "ISR.h"
#include "timers.h"
#include "batStatus.h"

#define IND_LED_PIN PB3

#define TURN_IND_LED_ON   do{PORTB |= (1 << IND_LED_PIN);}while(0)
#define TURN_IND_LED_OFF  do{PORTB &= ~(1 << IND_LED_PIN);}while(0)
#define TOGGLE_IND_LED    do{PORTB ^= (1 << IND_LED_PIN);}while(0)

static void ILC_indicateLowBatt(void);
static void ILC_indicateDeadBatt(void);

void ILC_init(void)
{
  DDRB |= (1 << PB3);
  TURN_IND_LED_OFF;
}

void ILC_indicateControl(void)
{
	if(BATSTAT_batStatus() >= BATSTAT_BAT_LOW)
		TURN_IND_LED_ON;
	else
		TURN_IND_LED_OFF;

}

static void ILC_indicateLowBatt(void)
{
	
}

static void ILC_indicateDeadBatt(void)
{
	
}

void ILC_switchLed(uint8_t val)
{
  if(!val)
    TURN_IND_LED_OFF;
  else
    TURN_IND_LED_ON;
}

void ILC_toggleLed(void)
{
  TOGGLE_IND_LED;
}
