#include "ISR.h"
#include "indLedControl.h"

#define INTR_16MS (0<<WDP3)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0)
#define INTR_32MS (0<<WDP3)|(0<<WDP2)|(0<<WDP1)|(1<<WDP0)
static uint8_t ISR_timerFlag = 0;
static uint8_t ISR_BtFlag = 0;

ISR(WDT_vect) 
{
	ISR_timerFlag = 1;
}

ISR(INT0_vect) 
{
	ISR_BtFlag = 1; 
}

uint8_t ISR_flagSet(void)
{
	return ISR_timerFlag;
}

uint8_t ISR_BtTriggered(void)
{
	uint8_t returnVal = ISR_BtFlag;
	
	ISR_BtFlag = 0;
	return returnVal;
}

void ISR_clearFlag(void)
{
	ISR_timerFlag = 0; 
}

void ISR_init(void)
{
    // set timer to 0.5s
    WDTCR |= INTR_16MS;
    // Set watchdog timer in interrupt mode
    WDTCR |= (1<<WDTIE); // ISR enabled
    WDTCR |= (0<<WDE);   // No system reset
	
	ISR_enableBtIsr(); 
  
    sei(); // Enable global interrupts
}

void ISR_DisableBtIsr(void)
{
	GIMSK &= !(1<<INT0); // disable INT0 interrupt
}

void ISR_enableBtIsr(void)
{
	// Enable INT0 interrupt for waking and processing button presses
	// Triggers on a falling edge
	GIMSK |= (1<<INT0); // Enable INT0
	MCUCR |= (1<<ISC01);
}

