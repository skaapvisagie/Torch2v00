#ifndef ISR_HEADER
#define ISR_HEADER
#include <avr/interrupt.h>

#include "types.h"

void ISR_init(void);

//volatile uint8_t ISR_timerFlag = 0;

#endif
