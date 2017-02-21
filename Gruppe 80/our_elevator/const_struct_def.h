#pragma once

#include <iostream>
#include <vector>
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


std::vector<std::vector <Queue_element> > vector_init(){
    std::vector<std::vector <Queue_element> > temp;
    Queue_element init_element;
    init_element.active_button = 0;
    init_element.elevator_ID = -1;
    for (int i=0;i<N_FLOORS;i++){
        std::vector<Queue_element> rowvector;
        for(int j=0;j<N_BUTTONS;j++){
            rowvector.push_back(init_element);
        }
        temp.push_back(rowvector);
    }   
    return temp;
}
/*void print_status(Status status){
    std::cout <<"Dir: " << status.dir << "\nFloor: " << status.floor << "\nID: " << status.elevator_ID << "\nOut of order: " << status.out_of_order << std::endl;
}*/