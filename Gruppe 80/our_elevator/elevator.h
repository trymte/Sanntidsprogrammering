#include <queue.h>
#include <elev.h>


struct Status{
	Dirn dir;
	unsigned int floor;
	int elevator_ID;
	bool out_of_order;
};

class Elevator{
private:
	Status elevator_status;
	Queue_element** order_matrix_ptr;
	
public:
	Elevator(Status elevator_status)
	int get_floor(){return floor;}

	Dirn get_direction(){return dir;}

	int get_elevator_id(){return elevator_ID;}

	bool get_out_of_order_status(){return out_of_order;}

	void set_elevator_dir(Dirn dir){this->dir = dir;}

	void set_elevator_floor(unsigned int floor){this->floor = floor;}

	void set_elevator_ID(int elevator_ID){this->elevator_ID = elevator_ID;}

	void set_elevator_out_of_order(bool out_of_order){this->out_of_order = out_of_order;}

	~Elevator();
};




