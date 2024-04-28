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
  if (switch_state_changed) {
    P1OUT |= BIT0;
    blink_green();
  } else{
    P1OUT |= BIT6;
    blink_red();
  }
  switch_state_changed = 0;
}

