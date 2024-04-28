#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "incrementing.h"
void main(void) 
{ 
  switch_init();
  led_init();
  wdt_init();
  
  or_sr(0x18);  // CPU off, GIE on
} 
