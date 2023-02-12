#include "indLedControl.h"
#include "ISR.h"
#include "timers.h"
#include "batStatus.h"

#define IND_LED_PIN PB3

#define TURN_IND_LED_ON   do{PORTB |= (1 << IND_LED_PIN);}while(0)
#define TURN_IND_LED_OFF  do{PORTB &= ~(1 << IND_LED_PIN);}while(0)
#define TOGGLE_IND_LED    do{PORTB ^= (1 << IND_LED_PIN);}while(0)
	
#define LOW_BATT_INDC_TIME  	32u
#define DEAD_BATT_INDC_TIME 	16u

#define LOW_BATT_FLASH_COUNT	3u
#define DEAD_BATT_FLASH_COUNT 	4u

static void ILC_indicate(uint8_t flashes, uint8_t flashTime);

static bool StartInd = false; 

void ILC_init(void)
{
  DDRB |= (1 << PB3);
  TURN_IND_LED_OFF;
}

void ILC_indicateControl(void)
{
	if(StartInd)
	{
		switch(BATSTAT_batStatus())
		{
			case BATSTAT_BAT_LOW:
				ILC_indicate(LOW_BATT_FLASH_COUNT, LOW_BATT_INDC_TIME);
			break; 
				
			case BATSTAT_BAT_DEAD:
				ILC_indicate(DEAD_BATT_FLASH_COUNT, DEAD_BATT_INDC_TIME);
			break;
			
			case BATSTAT_BAT_STAT_UNKNOWN: // does not matter if bat stat is OK or unknown, it gets treared the same
			case BATSTAT_BAT_OK:
			
			break; 
		}	
	}	

}

static void ILC_indicate(uint8_t flashes, uint8_t flashTime)
{
	static uint8_t counter = 0;
	
	if(TIMRES_timerDone(E_TIMERS_indicationLedTimer))
	{
		TIMERS_startTimer(E_TIMERS_indicationLedTimer, flashTime);
		if(counter < flashes*2) // on and off
		{
			counter ++; 
			ILC_toggleLed();
		}
		else if(counter >= flashes*2)
		{
			TURN_IND_LED_OFF;
			counter = 0; 
			StartInd = false; 
		}
	}
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

void ILC_invokeIndStart(void)
{
	StartInd = true;
	TURN_IND_LED_OFF;
}