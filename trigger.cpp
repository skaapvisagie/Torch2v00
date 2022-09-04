#include "types.h"
#include "trigger.h"
#include "timers.h"

#define TRIGGER_PIN 0x02
#define TRIGGER_BLOCK_TIME 25u

static bool triggerFound = false; 
static bool getTrigger(void); 
static void checkTirgger(void);

void TRIGGER_init(void)
{
 PORTB |= (1 << PB1);  //activate pull-up resistor for PB1
 DDRB &= ~(1 << DDB1);    //set PB1 as input 
}

static bool getTrigger(void)
{
	return(!(PINB & TRIGGER_PIN)); //return(digitalRead(TRIGGER_PIN)^1); 
}

bool TRIGGER_triggerFound(void)
{
	return(triggerFound); 
}

void TRIGGER_restTrigger(void)
{
	triggerFound = false;
}

void TRIGGER_checkTirgger(void)
{	
	if(TIMRES_timerDone(E_TIMERS_triggerBlockTimer))
	{
		if(getTrigger())
		{
			TIMERS_startTimer(E_TIMERS_triggerBlockTimer, TRIGGER_BLOCK_TIME);
			triggerFound = true; 
		}
	}
}

