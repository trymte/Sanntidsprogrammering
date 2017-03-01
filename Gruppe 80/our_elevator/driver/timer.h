#pragma once


void timer_door_start(double duration);
void timer_door_stop(void);
int timer_door_timedOut(void);

/* Får problemer med timer stop, stopper begge timerene! Lage to timer-filer heller! 
void timer_condition_start(double duration);
void timer_condition_stop(void);
int timer_condition_timedOut(void);
*/
