#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>


//-------------------------------------------------------------------------------
//      Definition of structs and constants used in multiple files
//-------------------------------------------------------------------------------


const unsigned int N_FLOORS = 4;
const unsigned int N_BUTTONS = 3;
const unsigned int N_ELEVATORS = 3;

const unsigned int DOOR_TIME_S = 1;             // Door open time
const unsigned int TIME_CONDITION_S = 10;       // Duration allowed for an order to be finished

const unsigned int TIMER_DOOR_ID = 1;           // Id for the timer used for open door
const unsigned int TIMER_CONDITION_ID = 2;      // Id for the timer used to check out_of_order
 
const unsigned int MIN_MESSAGE_LENGTH = 69;     // Minimum allowed message length
const unsigned int NUMBER_OF_PINGS = 5;        // Number of pings used to determine connection


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
    MASTER_IP_INIT = 0,
    SLAVE_IP_INIT = 1,
    HANDSHAKE = 2,
    SLAVE_ORDER_COMPLETE = 3,
    SLAVE_ORDER_INCOMPLETE = 4,
    SLAVE_SEND_ELEVATOR_INFORMATION = 5,
    MASTER_DISTRIBUTE_ORDER_MATRIX = 6
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
    std::string ip;
	Dirn dir;
	int floor;
    int last_floor;
    State current_state;
	int elevator_ID;
	bool out_of_order;
	bool online;
    Role role;
};

//-------------------------------------------------------------------------------------------------------
//  Extra functions used in multiple cpp files
//-------------------------------------------------------------------------------------------------------

Status init_elev_status();

std::vector<std::vector<Queue_element> > init_twoD_vector(); 

std::vector<std::vector <Queue_element> > string_to_order_matrix(std::string &order_matrix_string);

std::string order_matrix_to_string(std::vector<std::vector <Queue_element> > *order_matrix_ptr);

void print_order_matrix(std::vector<std::vector <Queue_element> > *order_matrix_ptr);
