#ifndef ELEVATOR_H
#define ELEVATOR_H


#include "queue.h"

class Elevator{
private:
	//Dirn dir;
	int floor;
	int elevatorID;
	bool out_of_order;
	Queue_element** order_matrix_ptr;
public:
	Elevator(int dir, int floor, int elevatorID, bool out_of_order);
	int get_floor();
	int get_dir();
	int get_elev_id();


	//void set_elev_dir(Dirn dir);
	void set_elev_floor(unsigned int floor);
	void set_elev_ID(int elevator_ID);
	void set_elev_out_of_order(bool out_of_order);
};

#endif