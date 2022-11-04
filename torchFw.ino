#include "trigger.h"
#include "indLedControl.h"
#include "torchControl.h"
#include "batStatus.h"
#include "init.h"
#include "adc.h"
#include "timers.h"
#include "ISR.h"

//#define DEBUG
#ifdef DEBUG
  #include <SoftwareSerial.h>
  #define RX    6   // *** D3, Pin 6 PWM  Green
  #define TX    7   // *** D4, Pin 7 BT   Yellow
#endif

uint8_t test = 0;
void setup() 
{
  INIT_init();  
}

void loop() 
{
	ILC_indicateControl();
	TC_torchControl();
	Timers_UpdateTimers();
}
