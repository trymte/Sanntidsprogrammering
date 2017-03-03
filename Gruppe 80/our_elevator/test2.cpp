
#include "elevator.h"
#include "queue.h"
#include "network.h"
#include <stdio.h>
#include <iostream>





int main(){
    Queue my_queue;
	Network my_network;
    Elevator * my_elevator;
    my_elevator = my_network.get_elevator_ptr();


    return 0;
}