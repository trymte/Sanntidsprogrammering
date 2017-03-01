#include <stdio.h>
#include <sys/time.h>




static double get_wall_time(void){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


static  double          timerEndTime;
static  int             timerActive;

void timer_door_start(double duration){ //Duration in seconds
    timerEndTime    = get_wall_time() + duration;
    timerActive     = 1;
}

void timer_door_stop(void){
    timerActive = 0;
}

int timer_door_timedOut(void){
    return (timerActive  &&  get_wall_time() > timerEndTime);
}

/*

void timer_condition_start(double duration){ //Duration in seconds
    timerEndTime    = get_wall_time() + duration;
    timerActive     = 1;
}

void timer_condition_stop(void){
    timerActive = 0;
}

int timer_condition_timedOut(void){
    return (timerActive  &&  get_wall_time() > timerEndTime);
}

*/