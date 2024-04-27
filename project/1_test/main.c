//Initial test for just the LEDs make Red LED on and Green blink
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void){

  P1DIR |= LEDS;
  P1OUT ^= ~LED_GREEN;
  P1OUT &= ~LED_RED;

  or_sr(0x18);

}
