#include "init.h"
#include "trigger.h"
#include "indLedControl.h"


void INIT_init(void)
{
  TRIGGER_init();
  ILC_init();
  ADC_init();
}
