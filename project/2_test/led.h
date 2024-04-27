#ifndef led_included
#define led_included

#define LED_RED BIT0 //PT1.0
#define LED_GREEN BIT6 //PT1.6
#define LEDS (BIT0 | BIT6)

void green_Control(int on);
void red_Control(int on);
void blink_Lim();
#endif //included
