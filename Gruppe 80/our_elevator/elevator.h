#pragma once

#include "const_struct_def.h"



class Elevator{
private:
	Status elevator_status;
	std::vector<std::vector<Queue_element> > *order_matrix_ptr;
	
public:
	Elevator();

	Elevator(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix);

	Elevator(const Elevator &elevator);

	Status get_elevator_status(){return elevator_status;}

	std::vector<std::vector <Queue_element> >* get_order_matrix_ptr(){return this->order_matrix_ptr;}

	void set_elevator_order_matrix(std::vector<std::vector <Queue_element> > *order_matrix_ptr);

	void set_elevator_dir(Dirn dir){this->elevator_status.dir = dir;}

	void set_elevator_floor(unsigned int floor){this->elevator_status.floor = floor;}

	void set_elevator_ID(int elevator_ID){this->elevator_status.elevator_ID = elevator_ID;}

	void set_elevator_out_of_order(bool out_of_order){this->elevator_status.out_of_order = out_of_order;}

	void set_elevator_status(Status &status){this->elevator_status = status;}

	Elevator& operator=(const Elevator &rhs);

	~Elevator();
};




