#include "adc.h"

#define BAT_VOLTAGE     0x02
#define CURR_FEEDBACK   0x01
#define ADC_DIV_FACTOR  0x03 // xxxx x011 clk div 8

#define REF_VOLTAGE_BIT REFS0 //0x20 0b0100 0000

#define SET_REF_VCC     do{ADMUX &= ~(1 << REFS0);}                 while(0)
#define SET_REF_1V1     do{ADMUX |= (1 << REFS0);}                  while(0)
#define SEL_BATT_ADC    do{ADMUX |= (1 << BAT_VOLTAGE);}            while(0)
#define SEL_FB_ADC      do{ADMUX |= (1 << CURR_FEEDBACK);}          while(0)
#define ENABLE_ADC      do{ADCSRA |= (1 << ADEN);}                  while(0)
#define START_CONV      do{ADCSRA |= (1 << ADSC);}                 while(0)
#define DISABLE_ADC     do{ADCSRA &= ~(1 << ADEN);}                 while(0)
#define SET_PRE_SCALER  do{ADCSRA |= (1 << ADC_DIV_FACTOR);}        while(0)
#define WAIT_FOR_CONV   ADSC                                                  // conversion in progress/start bit

static uint16_t adc_result(void);

void ADC_init(void)
{

}

static uint16_t adc_result(void)
{
  return(ADCH << 8 | ADCL);
}

uint16_t ADC_getBatVoltage(void)
{
  uint16_t result = 0;
  
  SET_REF_VCC;
  SEL_BATT_ADC;
  ENABLE_ADC;
  START_CONV;
  while(WAIT_FOR_CONV); // wait for converison to be done
  result = adc_result();
  DISABLE_ADC;
  return(result);
  
}

uint16_t ADC_getFbVoltage(void)
{
  uint16_t result = 0;
  
  SET_REF_1V1;
  SEL_FB_ADC;
  ENABLE_ADC;
  START_CONV;
  while(WAIT_FOR_CONV); // wait for converison to be done
  result = adc_result();
  DISABLE_ADC;
  return(result);
}
