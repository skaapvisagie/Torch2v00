#include "batStatus.h"
#include "adc.h"

static uint8_t batStatus = BATSTAT_BAT_STAT_UNKNOWN; 

void BATSTAT_updateBatStatus(void)
{
  
}

uint8_t BATSTAT_batStatus(void)
{
  return(batStatus);
}
