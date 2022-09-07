#include "ISR.h"
#include "indLedControl.h"

#define INTR_16MS (0<<WDP3)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0)
#
static uint8_t ISR_timerFlag = 0;

ISR(WDT_vect) 
{
    ILC_toggleLed();
	ISR_timerFlag = 1;
}

uint8_t ISR_flagSet(void)
{
	return ISR_timerFlag;
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
    sei(); // Enable global interrupts
}
