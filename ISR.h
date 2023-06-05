#ifndef ISR_HEADER
#define ISR_HEADER

#include <avr/interrupt.h>

#include "types.h"

void ISR_init(void);

uint8_t ISR_flagSet(void);
uint8_t ISR_BtTriggered(void);
void ISR_clearFlag(void);
void ISR_DisableBtIsr(void);
void ISR_enableBtIsr(void);
void ISR_disableWdt(void);
void ISR_enableWdt(void);

#endif
