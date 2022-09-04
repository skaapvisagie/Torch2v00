#include "ISR.h"

volatile byte counter = 0;// interrupt needs volatile variable

ISR(TIMER0_OVF_vect) {
   if (++counter > 5) {// interrupt occurs 4.6 times per second
      // Toggle Port B pin 3 output state
      PORTB ^= 1<<PB3;// Toggle Port PB3
      counter = 0; //reset the counter
   }
}

void ISR_init(void)
{
   // Clear interrupts, just to make sure
   cli();
   // Set up Port B pin 3 mode to output by setting the proper bit
   // in the DataDirectionRegisterB
    //DDRB = 1<<DDB3;

   // set prescale timer to 1/1024th 
   TCCR0B |= (1<<CS02) | (1<<CS00);// set CS02 and CS00 bit in TCCR0B

   // enable timer overflow interrupt
   TIMSK0 |=1<<TOIE0;// left shift 1 to TOIE0 and OR with TIMSK
                     //  = set TOIE0 bit
   sei(); //start timer
}
