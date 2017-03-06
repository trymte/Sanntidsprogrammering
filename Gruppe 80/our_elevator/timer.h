#pragma once


void timer_start(double duration, unsigned int id);
void timer_stop(void);
int timer_timedOut(void);
unsigned int get_timer_id(void);
void set_timer_id(unsigned int id);

/* Får problemer med timer stop, stopper begge timerene! Lage to timer-filer heller! 
void timer_condition_start(double duration);
void timer_condition_stop(void);
int timer_condition_timedOut(void);
*/
