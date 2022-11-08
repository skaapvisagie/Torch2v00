#include "types.h"
#include "torchControl.h"
#include "batStatus.h"
#include "trigger.h"
#include "timers.h"
#include "adc.h"
#include "indLedControl.h"


#define DEBUG

#define PWM_PIN PB0

#define MODE_OFF	0x00u
#define MODE_LOW 	0x01u
#define MODE_MED 	0x02u
#define MODE_HIGH 	0x03u

#define OFF_CURR	0u    // 0mA      
#define LOW_CURR 	15u   // 500mA    
#define MED_CURR 	35u   // 1500mA
#define HIGH_CURR 60u   // 2500mA

#define ALPHA         3u
#define CURRTOLARANCE 5u

// Switching freq 10kHz
#define OFF_DUTYCYCLE 	0u
#define LOW_DUTYCYCLE 	51u
#define MED_DUTYCYCLE 	140u
#define HIGH_DUTYCYCLE 	229u

#define IN_PROGRESS     		    1u
#define MODE_CHANGE_DONE 		    0u
#define MODE_CHANGE_INC_COUNT	  10u
#define LED_CONTROL_INC			    1u

#define BATT_STATUS_UPDATE_TIME 1000u
#define CHANGE_MODE_TIME 		    240u
#define CURR_SAMPLE_AVG_TIME	  1u

/* When timer is set to Fast PWM Mode, the freqency can be
calculated using equation: F = F_CPU / (N * 256) 
Posible frequencies (@1.2MHz):
 -> F(N_1) 		= 4.687kHz
 -> F(N_8) 		= 585Hz
 -> F(N_64) 	= 73Hz
 -> F(N_256) 	= 18Hz
 -> F(N_1024) 	= 4Hz 		
 (x8 @9.6Mhz) */
 
#define N_1    (_BV(CS00))				      //= 37.5kHz  
#define N_8    (_BV(CS01))              //= 4.68kHz
#define N_64   (_BV(CS01)|_BV(CS00))    //= 584Hz
#define N_256  (_BV(CS02))              //= 144Hz
#define N_1024 (_BV(CS02)|_BV(CS00))    //= 32Hz 		

static void pwmSetup (void);
static void pwmStop(void);
static void pwmWrite (uint8_t val);
static uint8_t pwmRead(void);
static void pidControl(void);
static void detNewMode(void);
static uint8_t EMA(uint8_t currsample, uint8_t newSample);
static void brightnessControl(uint8_t current);
 
struct S_ledControl
{
	uint8_t targerCurrent;
	uint8_t mode;
	uint8_t battStatus;
};

static S_ledControl ledControl = { 	OFF_CURR,
									MODE_OFF,
									BATSTAT_BAT_STAT_UNKNOWN
									};

void TC_init(void)
{
	pwmSetup();
	pwmWrite(OFF_DUTYCYCLE);
	//ledControl.mode = MODE_LOW;
	//ledControl.targerCurrent = LOW_CURR;
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
 
static void pwmWrite(uint8_t val)
{
    OCR0A = val;
}

static uint8_t pwmRead(void)
{
  return(OCR0A);
}

void TC_torchControl(void)
{
   static uint8_t current = 0;
	
	 if(TRIGGER_triggerFound())
	 {
		 detNewMode();
     ILC_toggleLed();
	 }
   
	 current = EMA(current, ADC_getFbVoltage());
	 if(TIMRES_timerDone(E_TIMERS_currentSampleTimer))
   {
      TIMERS_startTimer(E_TIMERS_currentSampleTimer, CURR_SAMPLE_AVG_TIME); 
      if(ledControl.targerCurrent == OFF_CURR)
      {
        if(pwmRead())
          pwmWrite(pwmRead() - LED_CONTROL_INC*2); //decrement;
      }
      else
        brightnessControl(current);   
   }
}

static void detNewMode(void)
{	
	if(TIMRES_timerDone(E_TIMERS_changeModeTimer))
	{
    TIMERS_startTimer(E_TIMERS_changeModeTimer, CHANGE_MODE_TIME);
		if(ledControl.mode != MODE_OFF)
			ledControl.mode = MODE_OFF;
		else 
			ledControl.mode = MODE_LOW;
	}
	else
	{
		if(ledControl.mode >= MODE_HIGH)
			ledControl.mode = MODE_OFF;
		else 
   {
			ledControl.mode ++;
      TIMERS_startTimer(E_TIMERS_changeModeTimer, CHANGE_MODE_TIME); // reset timer
   }
	}
	
	switch(ledControl.mode)
	{
		case MODE_OFF: 
			ledControl.targerCurrent = OFF_CURR;
		break;
		
		case MODE_LOW:
			ledControl.targerCurrent = LOW_CURR;
		break;
		
		case MODE_MED:
			ledControl.targerCurrent = MED_CURR;
		break;
		
		case MODE_HIGH:
			ledControl.targerCurrent = HIGH_CURR;
		break; 
		
		default:
		break; 
	}
}

static uint8_t EMA(uint8_t currsample, uint8_t newSample)
{
	return (uint8_t)((newSample*ALPHA + currsample*(10-ALPHA))/10);
}

static void brightnessControl(uint8_t current)
{
//	if(ledControl.modeChange == IN_PROGRESS)
//	{
//		// current is close to target
//		if(current <= (ledControl.targerCurrent + (CURRTOLARANCE*2)) && current >= (ledControl.targerCurrent - (CURRTOLARANCE*2)) )
//		{
//			ledControl.modeChange = MODE_CHANGE_DONE;
//			increment = LED_CONTROL_INC;
//		}
//		else
//			increment = MODE_CHANGE_INC_COUNT;
//	}
//	else 
//		increment = LED_CONTROL_INC;


	if(current > (ledControl.targerCurrent + CURRTOLARANCE))
		pwmWrite(pwmRead() - LED_CONTROL_INC); //decrement;
	else if(current < (ledControl.targerCurrent - CURRTOLARANCE))
		pwmWrite(pwmRead() + LED_CONTROL_INC); //increment;

//	if(pwmVal >= 255)
//		pwmVal = 254;
//	
//	pwmWrite(pwmVal);
		
}

	

 
