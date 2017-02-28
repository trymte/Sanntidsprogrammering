#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

const unsigned int N_FLOORS = 4;
const unsigned int N_BUTTONS = 3;
const unsigned int N_ELEVATORS = 2;
const unsigned int DOOR_TIME_S = 3;

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


typedef enum { 
    Moving, 
    Idle, 
    Door_open
}State;

struct Queue_element{
    bool active_button;
    int elevator_ID;
};

struct Order{
    int floor;
    Button btn;
};


struct Status{
	Dirn dir;
	int floor;
    State current_state;
	int elevator_ID;
	bool out_of_order;
};

std::vector<std::vector<Queue_element> > twoD_vector_init(); 

std::vector<std::vector <Queue_element> > string_to_order_matrix(std::string &order_matrix_string);

std::string order_matrix_to_string(std::vector<std::vector <Queue_element> > *order_matrix_ptr);

/*void print_status(Status status){
    std::cout <<"Dir: " << status.dir << "\nFloor: " << status.floor << "\nID: " << status.elevator_ID << "\nOut of order: " << status.out_of_order << std::endl;
}*/