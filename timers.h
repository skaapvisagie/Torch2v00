#ifndef TIMERS
#define TIMERS

#include "types.h"

enum E_timer
{
	E_TIMERS_batStatusUpdateTimer = 0x00u,
	E_TIMERS_triggerBlockTimer,
	E_TIMERS_changeModeTimer,
	E_TIMERS_currentSampleTimer
};

void TIMERS_startTimer(uint8_t timer, uint8_t setTime);
void Timers_UpdateTimers(void);

bool TIMRES_timerDone(uint8_t timer);

#endif