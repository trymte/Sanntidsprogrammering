#include <iostream>
#include "driver/elev.h"



typedef enum { 
    B_HallUp = 0,
    B_HallDown = 1,
    B_Cab = 2
} Button;



int main(){
	elev_set_motor_direction(DIRN_DOWN);
}