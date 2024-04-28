#include <msp430.h>
#include "switches.h"
#include "incrementing.h"
/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){ //250 interrupts/1sec
  //second_Update(); // updates blinkLimit and seconds
  led_update();//manages leds control 
}
