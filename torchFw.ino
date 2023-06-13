#include "trigger.h"
#include "indLedControl.h"
#include "torchControl.h"
#include "batStatus.h"
#include "init.h"
#include "adc.h"
#include "timers.h"
#include "ISR.h"
#include <avr/sleep.h>

//#define DEBUG

void setup() 
{
  INIT_init();
}

void loop() 
{
	BATSTAT_updateBatStatus();
	ILC_indicateControl();
	TRIGGER_triggerControl();
	TC_torchControl();
	Timers_UpdateTimers();
	
	if(Timers_Sleep_Allowed() && TC_TorchOff())
		power_off();
}

static void power_off(void)
{
    // Prepare for sleep
#ifdef DEBUG    
	  ILC_switchLed(1); 
#endif

    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    // Go to sleep
    sei();
    sleep_cpu();

    // Clean up after sleep
    sleep_disable();
    
#ifdef DEBUG   
	  ILC_switchLed(0);
#endif
}
