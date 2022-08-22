#include "types.h"
#include "trigger.h"

#define TRIGGER_PIN 1

static bool getTrigger(void); 

void TRIGGER_init(void)
{
  pinMode(TRIGGER_PIN, INPUT_PULLUP); 
}

static bool getTrigger(void)
{
  return(digitalRead(TRIGGER_PIN)^1); 
}

void TRIGGER_sampleTrigger(void)
{
  
}

bool TRIGGER_triggerFound(void)
{
  return((bool)getTrigger()); 
}
