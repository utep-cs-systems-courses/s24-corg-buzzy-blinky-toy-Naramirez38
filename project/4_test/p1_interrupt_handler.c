#include <msp430.h>
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"
#include "led.h"
/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P1IFG &= ~SWITCHES;/* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & BIT0){
    P2IFG &= ~(BIT0);
    change_State(0);
  }

  if(P2IFG & BIT1){
    P2IFG &= ~(BIT1);
    change_State(1);
  }
  if(P2IFG & BIT2){
    P2IFG &= ~(BIT2);
    change_State(2);
  }
  if(P2IFG & BIT3){
    P2IFG &= ~(BIT3);
    change_State(3);
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){ //250 interrupts/1sec
  // second_Update(); // updates blinkLimit and seconds
  //led_update();//manages leds control
  s2_SM();
}
