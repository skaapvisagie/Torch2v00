#include "types.h"
#include "batStatus.h"
#include "adc.h"

static uint8_t batStatus = BATSTAT_BAT_STAT_UNKNOWN;    

#define BATT_FLAT 514u  //3v3
#define BATT_LOW  535u  //3v45
#define BATT_RMS  570u  //3v7
#define BATT_FULL 661u  //4v2           

void BATSTAT_updateBatStatus(void)
{
	uint8_t battVoltage = 0;
	
	battVoltage = (uint8_t)ADC_getBatVoltage();
	
	if(battVoltage <= BATT_FLAT)
		batStatus = BATSTAT_BAT_DEAD;
	
	else if(battVoltage <= BATT_LOW)
		batStatus = BATSTAT_BAT_LOW;
	
	else
		batStatus = BATSTAT_BAT_OK;
	
}

uint8_t BATSTAT_batStatus(void)
{
	return(batStatus);
}
