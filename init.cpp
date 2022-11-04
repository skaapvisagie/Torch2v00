#include "init.h"
#include "trigger.h"
#include "indLedControl.h"
#include "torchControl.h"
#include "ISR.h"

void INIT_init(void)
{
  TRIGGER_init();
  ILC_init();
  TC_init();
  ADC_init();
  ISR_init();
}
