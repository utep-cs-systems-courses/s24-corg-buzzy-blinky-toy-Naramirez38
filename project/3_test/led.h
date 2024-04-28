#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();		/* initialize LEDs */
void led_update();		/* update leds */

void blinkLim();
void green_Control(int on);
void red_Control(int on);
void blink_green();
void blink_red();
void blink_Update_Red();
void blink_Update_Green();
void wdt_init();

// these are boolean flags
extern unsigned char leds_changed, green_led_state, red_led_state;

#endif
