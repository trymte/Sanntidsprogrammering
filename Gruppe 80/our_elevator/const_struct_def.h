#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

const unsigned int N_FLOORS = 4;
const unsigned int N_BUTTONS = 3;
const unsigned int N_ELEVATORS = 2;
const unsigned int DOOR_TIME_S = 1;
const unsigned int TIME_CONDITION_S = 7;
const unsigned int TIMER_DOOR_ID = 1;
const unsigned int TIMER_CONDITION_ID = 2;



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
    SLAVE = 0,
    MASTER = 1
} Role;

typedef enum{
    SLAVE_REQUEST_ORDER_MATRIX = 0,
    SLAVE_ORDER_COMPLETE = 1,
    SLAVE_ORDER_INCOMPLETE = 2,
    SLAVE_SEND_ELEVATOR_INFORMATION = 3,
    MASTER_DISTRIBUTE_ORDER_MATRIX = 4
} Message;


typedef enum { 
    MOVING = 0, 
    IDLE = 1, 
    DOOR_OPEN = 2
}State;


struct Queue_element{
    bool active_button;
    int elevator_ID;
};

struct Order{
    bool active_order;
    int floor;
    Button btn;
};


struct Status{
    char* ip;
	Dirn dir;
	int floor;
    State current_state;
	int elevator_ID;
	bool out_of_order;
    Role role;
};



std::vector<std::vector<Queue_element> > twoD_vector_init(); 

std::vector<std::vector <Queue_element> > string_to_order_matrix(std::string &order_matrix_string);

std::string order_matrix_to_string(std::vector<std::vector <Queue_element> > *order_matrix_ptr);

Message message_id_string_to_enum(std::string str);

/*void print_status(Status status){
    std::cout <<"Dir: " << status.dir << "\nFloor: " << status.floor << "\nID: " << status.elevator_ID << "\nOut of order: " << status.out_of_order << std::endl;
}*/