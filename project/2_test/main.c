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
int blinkLimit = 0;
int blinkCount_r = 5;
int blinkCount_g = 6;

/*void blinkUpdate_green(){
  blinkCount_g--;
  if(blinkCount_g <= blinkLimit){
    blinkCount_g=6;
    red_control(1);
  } else {
    red_control(0);
  }
}
void blinkUpdate_red(){
  blinkCount_r++;
  if(blinkCount_r >= blinkLimit){
    blinkCount_r = 0;
    green_control(1);
  } else {
    green_control(0);
  }
}

void bothBlink(){
  blinkUpdate_green();
  blinkUpdate_red();
}
*/
void red_control(int on){
  if(on){
    P1OUT |= LED_RED;
  } else{
    P1OUT &= ~LED_RED;
  }
}
void green_control(int on){
  if(on){
    P1OUT |= LED_GREEN;
  } else{
    P1OUT &= ~LED_GREEN;
  }
}
/*
void second_Update(){
  static int countsec = 0;
  countsec++;
  if(countsec >= 250){
    countsec = 0;
    blinkLim();
  }
}

void blinkLim(){
  blinklimit++;
  if(blinklimit >= 8)
    blinklimit = 0;
}*/
void
__interrupt_vec(WDT_VECTOR) WDT(){
  blinkCount_r++;
  blinkCount_g--;
  if(blinkCount_g <= blinkLimit){
    blinkCount_g = 6;
    red_control(1);
  } else{
    red_control(0);
    }
  if(blinkCount_r >= blinkLimit){
    blinkCount_r = 0;
    green_control(1);
  } else {
    green_control(0);
  }  
  countsec++;
  if (countsec >= 250) { /* once each sec... */
    countsec = 0; /* reset count */
    blinkLimit++;   
    if(blinkLimit >= 8){
      blinkLimit = 0;
    }
  }
}
