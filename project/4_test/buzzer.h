#ifndef buzzer_included
#define buzzer_included
/*all values that will set the frqz of buzzer to proper song*/
#define F_3 0x2CB5 //175Hz
#define DB_4 0x1C25 //277Hz
#define D_4 0x1A95 //294Hz
#define EB_4 0x1914 //311Hz
#define E_4 0x17AC //330Hz
#define F_4 0x1685 //349Hz

void buzzer_init();
void buzzer_set_period(short cycles);
void measure_1(unsigned char input);
void measure_2();
void measure_3();
#endif // included
