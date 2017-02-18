#pragma once

#include <iostream>

const unsigned int N_FLOORS = 4;
const unsigned int N_BUTTONS = 3;
const unsigned int N_ELEVATORS = 2;

typedef enum { 
    D_Down  = -1,
    D_Stop  = 0, 
    D_Up    = 1 
} Dirn;

typedef enum { 
    B_HallUp = 0,
    B_HallDown = 1,
    B_Cab = 2
} Button;


struct Queue_element{
    bool active_button;
    int elevator_ID;
};

struct Order{
    unsigned int floor;
    Button btn;
};


struct Status{
	Dirn dir;
	unsigned int floor;
	int elevator_ID;
	bool out_of_order;
};

/*void print_status(Status status){
    std::cout <<"Dir: " << status.dir << "\nFloor: " << status.floor << "\nID: " << status.elevator_ID << "\nOut of order: " << status.out_of_order << std::endl;
}*/