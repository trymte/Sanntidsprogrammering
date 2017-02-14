#ifndef QUEUE_H
#define QUEUE_H


//#include "elevator.h"

//Constants to be moved
const unsigned int N_FLOORS = 4;
const unsigned int N_BUTTONS = 3;
const unsigned int N_ELEVATORS = 2;


//NB!!! Exists in elevator_io_types.h, may therefore be deleted! 
typedef enum { 
    B_HallUp = 0,
    B_HallDown = 1,
    B_Cab = 2
} Button;

typedef enum { 
    D_Down  = -1,
    D_Stop  = 0, 
    D_Up    = 1 
} Dirn;
//NB!!! Exists in elevator_io_types.h, may therefore be deleted! Nye verdier gjør det kompatibelt med queue_matrix

//Slettes, ligger i elevator.h
struct Elevator{
	int slettes;
};



struct Queue_element{
	bool active_button;
	int elevator_ID;
};

struct Order{
	unsigned int floor;
	Button btn;
};


//Kan flyttes til elevator.h
struct Status{
	Dirn dir;
	unsigned int floor;
	int elevator_ID;
	bool out_of_order;
};



class Queue{
private:
	unsigned int n_buttons; //Bytte ut til N_FLOORS fra elev.h
	unsigned int n_floors;
	Queue_element** order_matrix;

public:
	//Supposed to be private:
	unsigned int queue_calculate_cost(Order order, std::vector<Status>& status_vector);
	void queue_write_order_matrix();
	void queue_read_order_matrix();
	//


	Queue(unsigned int n_floors,unsigned int n_buttons);
	~Queue();

	void queue_add_order(Order new_order,int elevator_ID);
	Queue_element** queue_get_order_matrix();	
	void queue_merge_order_matrices(Queue queue_with_new_order_matrix); //Endre til UML std
	void queue_print_order_matrix();
	void assign_elevators_to_orders(Elevator &elevators);



	void queue_remove_order(Order order);
//	static void queue_assign_elevators_to_orders(Elevator &elevators);

	void queue_reset_orders(Status status);

};

#endif