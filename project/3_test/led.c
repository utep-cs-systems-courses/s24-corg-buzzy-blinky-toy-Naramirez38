#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "incrementing.h"
void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  unsigned char led_Flags = 0;
  led_Flags |= switch_state_down ? LED_GREEN : 0;
  led_Flags |= switch_state_down ? 0 : LED_RED;
  
  if(switch_state_changed) {
    while(P1IN & SWITCHES){
    P1OUT &= (0xFF-LEDS)|led_Flags;
    //P1OUT &= ~BIT0;
    //time_Adv_SM_Red();
    //time_Adv_SM_Green();
    }
  }else{
    P1OUT &= (0xFF-LEDS)|led_Flags;
    // P1OUT &= ~BIT6;
    time_Adv_SM_Green();
    //time_Adv_SM_Red();
  }
  switch_state_changed = 0;
}

