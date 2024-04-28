
//Initial test for just the LEDs make Red LED on and Green blink
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "incrementing.h"
void wdt_init(){
  
  configureClocks();
  enableWDTInterrupts();

}

static int blinkLimit = 3;
void blink_Update_Green(){
  static int blinkCount_g = 0;
  blinkCount_g--;
  if(blinkCount_g <= blinkLimit){
    blinkCount_g=6;
    P1OUT &= ~BIT0;
    green_Control(1);
  } else {
    P1OUT &= ~BIT0;
    green_Control(0);
  }
}

void blink_Update_Red(){
  static int blinkCount_r = 0;
  blinkCount_r++;
  if(blinkCount_r >= blinkLimit){
    blinkCount_r = 0;
    P1OUT &= ~BIT6;
    red_Control(1);
  } else {
    P1OUT &= ~BIT6;
    red_Control(0);
  }
}

void blink_green(){ //controls and calls the 2 updates for green and red led
  blink_Update_Green(); //self explanatory
  
}

void blink_red(){
  blink_Update_Red();// self explanatory
}

void red_Control(int on){ //control red LED
  if(on){
    P1OUT |= LED_RED;
  } else{
    P1OUT &= ~LED_RED;
  }
}

void green_Control(int on){ //controls green LED
  if(on){
    P1OUT |= LED_GREEN;
  } else{
    P1OUT &= ~LED_GREEN;
  }
}

void second_Update(){ //called 250 times per second 250 calls/ 1 sec = 1 call = 1/250sec
  static int countsec = 0;
  countsec++;
  if(countsec >= 250){ 
    countsec = 0;
    blink_Lim();
  }
}

void blink_Lim(){
  blinkLimit++;
  if(blinkLimit >= 8)
    blinkLimit= 0;
}

void time_Adv_SM_Green(){
  blink_green(); // handles green LED statemachines
  second_Update(); // updates seconds same clock as red
}
void time_Adv_SM_Red(){
  blink_red();//handles red LED statemachine
  second_Update(); // updates seconds same clock as green
}

