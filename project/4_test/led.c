#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "incrementing.h"

unsigned char led_Flags, state = 0;
void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}
void led_Off(){
  P1OUT &= ~(LEDS);
}
void led_update(){
  led_Flags |= switch_state_down ? LED_GREEN : 0;
  led_Flags |= switch_state_down ? 0 : LED_RED;
  
  if(switch_state_down & (state == 1)) {
    P1OUT &= (0xFF - LEDS)|led_Flags;
    blinkers_Green();
  }else{
    P1OUT &= (0xFF - LEDS) | led_Flags;
    blinkers_Red();
  }
  switch_state_changed = 0;
}

void blinkers_Green(){
    P1OUT &= (0xFF - LEDS) | led_Flags;
    P1OUT &= ~BIT0;
    time_Adv_SM_Green();
}
void blinkers_Red(){
    P1OUT &= (0xFF - LEDS) | led_Flags;
    P1OUT &= ~BIT6;
    time_Adv_SM_Red();
}

void change_State(short new_state){
  state = new_state;
  s2_SM();
}

void
s2_SM(){
  unsigned short counted_why_not = 0;
  switch(state){

  case 0:
    blinkers_Red();
    break;

  case 1:
    blinkers_Green();
    break;
      
  case 2:
    if(switch_state_down){
      state = 0;
    }
    break;

  case 3:
    led_Off();
    break;
      
  default:
    if((state >= 4) | (state < 0)){
      state = 0;
    }
    break;
  }
}

