#include "types.h"
#include "batStatus.h"
#include "adc.h"
#include "timers.h"
#include "indLedControl.h"

#define BATT_STAT_UPDATE_TIME 240u
static uint8_t batStatus = BATSTAT_BAT_STAT_UNKNOWN; 

static uint8_t avgBattSamples(void);   

#define BATT_FLAT 129u  //3v3
#define BATT_LOW  132u  //3v45
#define BATT_RMS  140u  //3v7
#define BATT_FULL 158u  //4v2   

#define SAMPLE_SIZE 10u        

void BATSTAT_updateBatStatus(void)
{
	uint8_t battVoltage = 0;
	
	// battVoltage = avgBattSamples();
	// if(battVoltage >= BATT_LOW)
		// ILC_switchLed(ILC_LED_ON);
	// else 
		// ILC_switchLed(ILC_LED_OFF);
	
	if(TIMRES_timerDone(E_TIMERS_batStatusUpdateTimer))
	{
		TIMERS_startTimer(E_TIMERS_batStatusUpdateTimer, BATT_STAT_UPDATE_TIME);
		
		battVoltage = (uint8_t)ADC_getBatVoltage();
		
		if(battVoltage <= BATT_FLAT)
			batStatus = BATSTAT_BAT_DEAD;
		
		else if(battVoltage <= BATT_LOW)
			batStatus = BATSTAT_BAT_LOW;
		
		else
			batStatus = BATSTAT_BAT_OK;
	} 	
	
}

uint8_t BATSTAT_batStatus(void)
{
	return(batStatus);
}

static uint8_t avgBattSamples(void)
{
	// uint16_t avg = 0;
	// uint8_t i = 0;
	
	// for(i = 0; i < SAMPLE_SIZE; i++)
	// {
		// avg = avg + (uint8_t)ADC_getBatVoltage();
	// }
	
	// return((uint8_t)(avg/SAMPLE_SIZE));
	
}
