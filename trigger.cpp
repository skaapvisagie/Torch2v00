#include "trigger.h"

#define TRIGGER_PIN 1

static bool getTrigger(void); 

void TRIGGER_init(void)
{
  pinmode(TRIGGER_PIN, INPUT_PULLUP); 
}

static bool getTrigger(void)
{
  return(digitalRead(TRIGGER_Pin)); 
}

void TRIGGER_sampleTrigger(void)
{
  
}

bool TRIGGER_triggerFound(void)
{
  
}
