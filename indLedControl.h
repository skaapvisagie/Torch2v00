#ifndef INDICATION_CONTROL
#define INDICATION_CONTROL

#include "types.h"

#define ILC_LED_OFF 0x00u
#define ILC_LED_ON  0x01u

void ILC_init(void);
void ILC_indicateControl(void);

void ILC_switchLed(uint8_t val);
void ILC_toggleLed(void);
void ILC_invokeIndStart(void);

#endif
