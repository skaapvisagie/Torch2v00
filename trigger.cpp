#include "types.h"
#include "trigger.h"
#include "timers.h"
#include "ISR.h"
#include "indLedControl.h"

#define TRIGGER_PIN 0x02
#define TRIGGER_BLOCK_TIME 25u

static bool triggerFound = false;

void TRIGGER_init(void)
{
	PORTB |= (1 << PB1);  //activate pull-up resistor for PB1
	DDRB &= ~(1 << DDB1);    //set PB1 as input 
}

bool TRIGGER_triggerFound(void)
{
	bool returnVal = triggerFound; 
	
	triggerFound = false; 
	
	return(returnVal);
}

void TRIGGER_triggerControl(void) 
{
	static bool startDebouce = false; 
	
	if(ISR_BtTriggered())
	{
		startDebouce = true;
		triggerFound = true; 
		ISR_DisableBtIsr(); 
		TIMERS_startTimer(E_TIMERS_triggerBlockTimer, TRIGGER_BLOCK_TIME);
	}

	if(startDebouce)
	{
		if(TIMRES_timerDone(E_TIMERS_triggerBlockTimer))
			ISR_enableBtIsr();
	}
		
}
