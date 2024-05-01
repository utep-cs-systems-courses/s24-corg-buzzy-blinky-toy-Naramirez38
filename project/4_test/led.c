#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"
unsigned char measures, notes_play,notes, was_Pressed, gone_Once, led_Flags, state = 0;
unsigned long frqz = 4000;
void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}
void led_Off(){
  P1OUT &= ~(LEDS);
}
void buzzer_Update(){ //used to be led_Update
  //led_Flags |= switch_state_down ? LED_GREEN : 0;
  //led_Flags |= switch_state_down ? 0 : LED_RED;
  
  if(switch_state_down) {
    if(gone_Once == 0){
      gone_Once ++;
      frqz -= 0xC4;//100
    }
    buzzer_set_period(frqz);
    if(frqz > 0x1388){//3500
      frqz = 0xDAC;//5000
    }
    //P1OUT &= (0xFF - LEDS)|led_Flags;
    //blinkers_Green();
  }else{
    gone_Once = 0;
    buzzer_set_period(0);
    //P1OUT &= (0xFF - LEDS) | led_Flags;
    //blinkers_Red();
  }
  switch_state_changed = 0;
}

void led_update(){
  unsigned char led_Flags = 0;
  
  //led_Flags |= switch_state_down ? LED_GREEN : 0;
  //led_Flags |= switch_state_down ? 0 : LED_RED;
  /*
  if(switch_state_down) {
     P1OUT &= (0xFF - LEDS) | led_Flags;
     P1OUT &= ~BIT0;
    time_Adv_SM_Green();
  }else{
    P1OUT &= (0xFF-LEDS)|led_Flags;
    P1OUT &= ~BIT6;
    time_Adv_SM_Red();
    }*/
  // switch_state_changed = 0;
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
  switch(state){

  case 0:
    blinkers_Red();
    break;

  case 1:
    blinkers_Green();
    break;
      
  case 2:
    buzzer_set_period(frqz);
    /*if(switch_state_down){
      state = 0;
      }*/
    break;

  case 3:
    led_Off();
    buzzer_set_period(0);
    break;
      
  default:
    buzzer_set_period(0);
    if((state >= 4) | (state < 0)){
      state = 0;
    }
    break;
  }
}
void
change_Note(char new_Note){
  notes = new_Note;
  s3_SM();
}

void
s3_SM(){
  switch(notes_play){
  case '1':
    buzzer_set_period(F_3);
    break;

  case '2':
    buzzer_set_period(DB_4);
    break;

  case '3':
    buzzer_set_period(D_4);
    break;
  case '4':
    buzzer_set_period(EB_4);
    break;
  case '5':
    buzzer_set_period(E_4);
    break;
  case '6':
    buzzer_set_period(F_4);
    
  default:
    buzzer_set_period(0);
    break;
  }
}

void
s3_SM_Measures(){
  switch(measures){
  case '1':
    switch(notes){
    case '1':
      notes_play = 1;
      s3_SM();
      break;
    case '2':
      notes_play = 0;
      s3_SM();
      notes_play = 1;
      s3_SM();
      break;
    case '3':
      notes_play = 6:
      s3_SM();
      break;
    case '4':
      notes_play = 1;
      s3_SM();
      break;
    case '5':
      notes_play = 0;
      s3_SM();
      notes_play = 1;
      s3_SM();
      break;
    case '6':
      notes_play = 5;
      s3_SM();
      break;
    case '7':
      notes_play = 1;
      s3_SM();
      break;
    case '8':
      notes_play = 0;
      s3_SM();
      notes_play = 1;
      s3_SM();
      break;
    default:
      buzzer_set_period(0);
    } 
    break;
  case '2':
    switch(notes){
    case '1':
      notes_play = 4;
      s3_SM();
      break;
    case '2':
      notes_play = 1;
      s3_SM();
      break;
    case '3':
      notes_play = 0;
      s3_SM();
      notes_play = 1;
      s3_SM();
      break;
    case '4':
      notes_play = 3;
      s3_SM();
      break;
    case '5':
      notes_play = 1;
      s3_SM();
      break;
    case '6':
      notes_play = 0;
      s3_SM();
      notes_play = 1;
      s3_SM();
      break;
    case '7':
      notes_play = 2;
      s3_SM();
      break;
    case '8':
      notes_play = 3;
      s3_SM()
      break;
    default:
      buzzer_set_period(0);
      break;
    }
    break;
  case '3':
    measures = 1;
    s3_SM_Measures();
    break;
  default:
    buzzer_set_period(0);
    break;
  } 


}
