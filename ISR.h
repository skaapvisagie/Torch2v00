#ifndef ISR_HEADER
#define ISR_HEADER

#include <avr/interrupt.h>

#include "types.h"

void ISR_init(void);

uint8_t ISR_flagSet(void);
void ISR_clearFlag(void);

#endif
