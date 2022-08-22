#ifndef TRIGGER
#define TRIGGER

//#include <Wire.h>

void TRIGGER_init(void); 
void TRIGGER_sampleTrigger(void);

bool TRIGGER_triggerFound(void);

#endif
