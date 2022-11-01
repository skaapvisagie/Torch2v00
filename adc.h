#ifndef ADC_H
#define ADC_H

#include "types.h"

void ADC_init(void);

uint8_t ADC_getBatVoltage(void);
uint8_t ADC_getFbVoltage(void);

#endif
