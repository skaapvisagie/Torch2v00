#include "adc.h"
#include "indLedControl.h"

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

#define BATT_READ_SETUP do{ ADMUX = 0b00100010; ADCSRA = 0b10000011;}   while(0)
#define FB_READ_SETUP   do{ ADMUX = 0b01100001; ADCSRA = 0b10000011;}   while(0)

static uint16_t adc_result(void);

void ADC_init(void)
{
//  SET_PRE_SCALER;
//  ADCSRA &= ~(1 << ADLAR); // align right
//  DISABLE_ADC;
//  ADMUX = 0b00100010;   //sets 1.1V IRV, sets ADC3 as input channel,
//          //and left adjusts
//  ADCSRA = 0b10000011;  //turn on ADC, keep ADC single conversion mode,
//                      //and set division factor-8 for 125kHz ADC clock
}

static uint16_t adc_result(void)
{
  return((uint16_t)((ADCH << 8) | ADCL));
}

uint8_t ADC_getBatVoltage(void)
{
  DISABLE_ADC;
  BATT_READ_SETUP; 
  START_CONV;
  while(ADCSRA & (1 << ADSC)); 
  return(ADCH);               
}

uint8_t ADC_getFbVoltage(void)
{
  DISABLE_ADC;
  FB_READ_SETUP; 
  START_CONV;
  return(ADCH); 
}
