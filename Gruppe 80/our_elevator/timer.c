#include <stdio.h>
#include <sys/time.h>
#include "utilities.h"




static double get_wall_time(void){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


static  double          timerEndTime;
static  int             timerActive;
int timer_id;
int* timer_id_ptr = &timer_id;

void timer_start(double duration, unsigned int id){ //Duration in seconds
    //if(timer_id == 0){
    timerEndTime    = get_wall_time() + duration;
    timerActive     = 1;
    *timer_id_ptr = id;
    //} 
}

void timer_stop(void){
    timerActive = 0;
    *timer_id_ptr = 0;
}

int timer_timedOut(void){
    return (timerActive  &&  get_wall_time() > timerEndTime);
}

unsigned int get_timer_id(){
    return timer_id;
}

void set_timer_id(unsigned int id){
    *timer_id_ptr = id;
}

