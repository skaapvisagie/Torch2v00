#ifndef TRIGGER
#define TRIGGER

//#include <Wire.h>

void TRIGGER_init(void); 
void TRIGGER_restTrigger(void);
void TRIGGER_checkTirgger(void);

bool TRIGGER_triggerFound(void);
void TRIGGER_triggerControl(void);

#endif
