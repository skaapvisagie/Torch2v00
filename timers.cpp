#include "timers.h"
#include "ISR.h"

#define Max_Char_Size   255u
#define Tmr1_Flag       10u

static bool Allow_Sleep             = false; 

static uint8_t batStatusUpdateTimer = 0x00u;
static uint8_t triggerBlockTimer    = 0x00u;
static uint8_t changeModeTimer      = 0x00u;

extern volatile uint8_t Tmr1_Timer1_Flag;
extern volatile uint8_t IOC_source;

void TIMERS_startTimer(uint8_t timer, uint8_t setTime)
{
    switch(timer)
    {
        case E_TIMERS_batStatusUpdateTimer:
            if(setTime <= Max_Char_Size)
                batStatusUpdateTimer = setTime;
        break;
        
        case E_TIMERS_triggerBlockTimer:
            triggerBlockTimer = setTime;
        break;
        
        case E_TIMERS_changeModeTimer:
             changeModeTimer = setTime;
        break;
    }
}

bool TIMRES_timerDone(uint8_t timer)
{
    switch(timer)
    {
        case E_TIMERS_batStatusUpdateTimer:
            return (bool)((!batStatusUpdateTimer) ? true : false);
        
        case E_TIMERS_triggerBlockTimer:
            return (bool)((!triggerBlockTimer) ? true : false);
        
        case E_TIMERS_changeModeTimer:
            return (bool)((!changeModeTimer) ? true : false);

        default:
            return false; 
    }
}

void Timers_UpdateTimers(void)
{
    // static uint8_t counter = 0; 
    // static uint8_t Timer1  = 0;
    
    // if(Tmr1_Timer1_Flag)
    // {
        // Tmr1_Timer1_Flag = 0;
        
        // if(Debounce_Timer)
        // {
            // Allow_Sleep = false;
            // Debounce_Timer--;
        // }
        
        // if(counter)
            // counter--;
        // else
        // {
            // Timer1 = 1;
            // counter = Tmr1_Flag; 
        // }
    // }
	
    if(ISR_flagSet())
    {
        Allow_Sleep = true;
        
        ISR_clearFlag(); 
        
        if(batStatusUpdateTimer)
        {
            Allow_Sleep = false; 
            batStatusUpdateTimer--;
        }

        if(triggerBlockTimer)
        {
            Allow_Sleep = false;
            triggerBlockTimer--;
        }

        if(changeModeTimer)
        {
            Allow_Sleep = false;
            changeModeTimer--;
        }      
    }
}

bool Timers_Sleep_Allowed(void)
{
    return Allow_Sleep; 
}
