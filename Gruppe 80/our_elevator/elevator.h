//#include "queue.h"
//#include "../driver/elev.h"




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


struct Status{
	Dirn dir;
	unsigned int floor;
	int elevator_ID;
	bool out_of_order;
};
/*
struct Queue_element{
	bool active_button;
	int elevator_ID;
};
*/

class Elevator{
private:
	Status elevator_status;
	Queue_element** order_matrix_ptr;
	
public:
	Elevator();

	Elevator(Status elevator_status);

	Elevator(const Elevator &elevator);

	Status get_elevator_status(){return elevator_status;}

	Queue_element** get_order_matrix_ptr(){return this->order_matrix_ptr;}

	void set_elevator_dir(Dirn dir){this->elevator_status.dir = dir;}

	void set_elevator_floor(unsigned int floor){this->elevator_status.floor = floor;}

	void set_elevator_ID(int elevator_ID){this->elevator_status.elevator_ID = elevator_ID;}

	void set_elevator_out_of_order(bool out_of_order){this->elevator_status.out_of_order = out_of_order;}

	~Elevator();
};





