//Initial test for just the LEDs make Red LED on and Green blink
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void){

  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();
  enableWDTInterrupts();
  
  or_sr(0x18);

}

int countsec = 0;
int blinklimit = 5;
int blinkCount = 0; 

void
__interrupt_vec(WDT_VECTOR) WDT(){
  countsec++;
  if (countsec >= 250) { /* once each sec... */
    countsec = 0; /* reset count */
    P1OUT ^= LED_GREEN; /* toggle red LED */
    P1OUT ^= LED_RED; /* toggle green LED*/
  }

}
