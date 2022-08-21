#include "adc.h"


#define BAT_VOLTAGE_PIN   4
#define CURR_FEEDBACK_PIN 2

uint16_t ADC_getBatVoltage(void)
{
  return(analogRead(BAT_VOLTAGE_PIN));
}

uint16_t ADC_getFbVoltage(void)
{
  return(analogRead(CURR_FEEDBACK_PIN));
}
