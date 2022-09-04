#include "adc.h"

#define BAT_VOLTAGE     0x02
#define CURR_FEEDBACK   0x01
#define ADC_DIV_FACTOR  0x03  //xxxx x011 clk div 8
#define REF_VOLTAGE_BIT REFS0 //0x20 0b0100 0000

#define SET_REF_VCC     do{ADMUX &= ~(1 << REFS0);}                     while(0)
#define SET_REF_1V1     do{ADMUX |= (1 << REFS0);}                      while(0)
#define SEL_BATT_ADC    do{ADMUX |= (1 << MUX1); ADMUX &= ~(1 << MUX0);}while(0)
#define SEL_FB_ADC      do{ADMUX |= (1 << MUX0); ADMUX &= ~(1 << MUX1);}while(0)
#define ENABLE_ADC      do{ADCSRA |= (1 << ADEN);}                      while(0)
#define START_CONV      do{ADCSRA |= (1 << ADSC);}                      while(0)
#define DISABLE_ADC     do{ADCSRA &= ~(1 << ADEN);}                     while(0)
#define SET_PRE_SCALER  do{ADCSRA |= (1 << ADC_DIV_FACTOR);}            while(0)
#define WAIT_FOR_CONV   while(ADCSRA & (1 << ADSC)){}                        // conversion in progress/start bit


static uint16_t adc_result(void);

void ADC_init(void)
{
  SET_PRE_SCALER;
  ADCSRA &= ~(1 << ADLAR); // align right
  DISABLE_ADC;
}

static uint16_t adc_result(void)
{
  return((uint16_t)(ADCL | (ADCH & 0x03) << 8));
}

uint16_t ADC_getBatVoltage(void)
{
  SEL_BATT_ADC;
  SET_REF_VCC;
  ENABLE_ADC;
  START_CONV;
  WAIT_FOR_CONV; // wait for converison to be done
  DISABLE_ADC;
  return(adc_result());
  
}

uint16_t ADC_getFbVoltage(void)
{
  SET_REF_1V1;
  SEL_FB_ADC;
  ENABLE_ADC;
  START_CONV;
  WAIT_FOR_CONV; // wait for converison to be done
  DISABLE_ADC;
  return(adc_result());
}

