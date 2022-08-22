#include "types.h"
#include "trigger.h"

#define TRIGGER_PIN 0x02

static bool getTrigger(void); 

void TRIGGER_init(void)
{
 PORTB |= (1 << PB1);  //activate pull-up resistor for PB1
 DDRB &= ~(1 << DDB1);    //set PB1 as input 
}

static bool getTrigger(void)
{
  return(!(PINB & TRIGGER_PIN)); //return(digitalRead(TRIGGER_PIN)^1); 
}

void TRIGGER_sampleTrigger(void)
{
  
}

bool TRIGGER_triggerFound(void)
{
  return(getTrigger()); 
}
