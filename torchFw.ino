#include "trigger.h"
#include "indLedControl.h"
#include "torchControl.h"
#include "batStatus.h"
#include "init.h"
#include "adc.h"
#include "timers.h"
#include "ISR.h"

//#define DEBUG

void setup() 
{
  INIT_init();
}

void loop() 
{
	//ILC_indicateControl();
	TC_torchControl();
	Timers_UpdateTimers();
}
