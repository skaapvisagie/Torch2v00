#ifndef ADC
#define ADC
#include "types.h"

void ADC_init(void);

uint16_t ADC_getBatVoltage(void);
uint16_t ADC_getFbVoltage(void);

#endif
