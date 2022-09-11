#include "types.h"
#include "torchControl.h"
#include "batStatus.h"
#include "trigger.h"
#include "PID.h"
#include "timers.h"
#include "adc.h"

#define PWM_PIN PB0

#define OFF		0x00u
#define LOW 	0x01u
#define MED 	0x02u
#define HIGH 	0x03u

#define OFF_CURR	0u // 0mA
#define LOW_CURR 	47u // 500mA
#define MED_CURR 	140u // 1500mA
#define HIGH_CURR 	233u // 2500mA

#define ALPHA 3u
#define CURRTOLARANCE 10u

// Switching freq 10kHz
#define OFF_DUTYCYCLE 	0u
#define LOW_DUTYCYCLE 	51u
#define MED_DUTYCYCLE 	92u
#define HIGH_DUTYCYCLE 	229u

#define IN_PROGRESS     		1u
#define MODE_CHANGE_DONE 		0u
#define MODE_CHANGE_INC_COUNT	10u
#deifne LED_CONTROL_INC			1u

#define BATT_STATUS_UPDATE_TIME 1000u
#define CHANGE_MODE_TIME 		100u
#define CURR_SAMPLE_AVG_TIME	1u

/* When timer is set to Fast PWM Mode, the freqency can be
calculated using equation: F = F_CPU / (N * 256) 
Posible frequencies (@1.2MHz):
 -> F(N_1) 		= 4.687kHz
 -> F(N_8) 		= 585Hz
 -> F(N_64) 	= 73Hz
 -> F(N_256) 	= 18Hz
 -> F(N_1024) 	= 4Hz 		
 (x8 @9.6Mhz) */
 
#define N_1    (_BV(CS00))				//= 37.5kHz  
#define N_8    (_BV(CS01))              //= 4.68kHz
#define N_64   (_BV(CS01)|_BV(CS00))    //= 584Hz
#define N_256  (_BV(CS02))              //= 144Hz
#define N_1024 (_BV(CS02)|_BV(CS00))    //= 32Hz 		

static void pwmSetup (void);
static void pwmStop(void);
static void pwmWrite (uint8_t val);
static void pidControl(void);
static void detNewMode(void);
static uint8_t EMA(uint8_t currsample, uint8_t newSample);
static void brightnessControl(uint8_t current)
 
struct S_ledControl
{
	uint8_t targerCurrent;
	uint8_t mode;
	uint8_t battStatus;
	uint8_t modeChange;
	
};

static S_ledControl ledControl = { 	OFF_CURR,
									OFF,
									BATSTAT_BAT_STAT_UNKNOWN,
									0
									};

void TC_init(void)
{
	pwmSetup();
	pwmWrite(LOW_DUTYCYCLE);
}

static void pwmSetup (void)
{
    DDRB |= _BV(PWM_PIN); // set PWM pin as OUTPUT
    TCCR0A |= _BV(WGM01)|_BV(WGM00); // set timer mode to FAST PWM
    TCCR0A |= _BV(COM0A1); // connect PWM signal to pin (AC0A => PB0)
	TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | N_1; // set prescaler
}

static void pwmStop(void)
{
    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
}
 
static void pwmWrite (uint8_t val)
{
    OCR0A = val;
}

void TC_torchControl(void)
{
	static uint8_t current = 0;
	
	if(TRIGGER_triggerFound())
	{
		detNewMode();
		TRIGGER_restTrigger();
	}
	if(TIMRES_timerDone(E_TIMERS_currentSampleTimer))
	{
		TIMERS_startTimer(E_TIMERS_currentSampleTimer, CURR_SAMPLE_AVG_TIME);
		brightnessControl(currnet);
	}
	else
	{
		current = EMA(current, ADC_getFbVoltage());
	}
}

static void detNewMode(void)
{	
	if(TIMRES_timerDone(E_TIMERS_changeModeTimer))
	{
		if(ledControl.mode != OFF)
			ledControl.mode = OFF;
		else 
			ledControl.mode = LOW;
	}
	else
	{
		if(ledControl.mode >= HIGH)
			ledControl.mode = OFF;
		else 
			ledControl.mode ++;
	}
	
	switch(ledControl.mode)
	{
		case OFF: 
			ledControl.targerCurrent = OFF_CURR;
		break;
		
		case LOW:
			ledControl.targerCurrent = LOW_CURR;
		break;
		
		case MED:
			ledControl.targerCurrent = MED_CURR;
		break;
		
		case HIGH:
			ledControl.targerCurrent = HIGH_CURR;
		break; 
		
		default:
		break; 
	}
	ledControl.modeChange = IN_PROGRESS; 
	TIMERS_startTimer(E_TIMERS_changeModeTimer, CHANGE_MODE_TIME);
}

static uint8_t EMA(uint8_t currsample, uint8_t newSample)
{
	return (uint8_t)((newSample*ALPHA + currsample*(10-ALPHA))/10);
}

static void brightnessControl(uint8_t current)
{
	static uint8_t increment  	= 0;
	static uint8_t pwmVal 		= 0; 
	
	if(ledControl.modeChange == IN_PROGRESS)
	{
		if(currnet <= (ledControl.targerCurrent + (CURRTOLARANCE*2)) && currnet >= (ledControl.targerCurrent - (CURRTOLARANCE*2)) )
		{
			ledControl.modeChange = MODE_CHANGE_DONE;
			increment = LED_CONTROL_INC;
		}
		else
			increment = MODE_CHANGE_INC_COUNT;
	}
	else 
		increment = LED_CONTROL_INC;
	
	if(current > (ledControl.targerCurrent + CURRTOLARANCE))
		pwmVal -= increment;
	else if(currnet < (ledControl.targerCurrent - CURRTOLARANCE))
		pwmVal += increment;
	
	pwmWrite(pwmVal);
		
}

	

 
