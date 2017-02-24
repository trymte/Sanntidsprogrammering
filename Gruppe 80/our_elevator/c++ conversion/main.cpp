#include <iostream>

#include "elev.h"
#include "io.h"
#include "channels.h"

int main(){
	elev_init();

	elev_set_motor_direction(DIRN_STOP);
	std::cout << "I am here" << std::endl;
}