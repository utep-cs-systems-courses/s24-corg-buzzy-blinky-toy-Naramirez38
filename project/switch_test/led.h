#ifndef led_included
#define led_included

#define LED_RED BIT0 //P1.0
#define LED_GREEN BIT6 //P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3 //P1.3
#define SWITCHES SW1

void switch_interrupt_handler();


#endif //included
