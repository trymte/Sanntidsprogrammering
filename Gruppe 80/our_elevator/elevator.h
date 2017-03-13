#pragma once

#include "utilities.h"
#include "udp_sendrec.h"

class Elevator{
private:
	int order_matrix_ptr_count;
	Status elevator_status;
	std::vector<std::vector<Queue_element> > *order_matrix_ptr;	
public:
	Elevator();

	Elevator(Status elevator_status);

	Elevator(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix);

	Elevator(const Elevator &elevator);

	Elevator& operator=(const Elevator &rhs);

	~Elevator();
	
	
	void print_elevator();

	//-----------------------------------------------------------------------------------------------------------------
	// Elevator get functions
	//-----------------------------------------------------------------------------------------------------------------

	Status get_status(){return this->elevator_status;}

	bool get_condition(){return this->elevator_status.online && !this->elevator_status.out_of_order;}

	std::vector<std::vector <Queue_element> >* get_order_matrix_ptr(){return this->order_matrix_ptr;}

	//-----------------------------------------------------------------------------------------------------------------
	// Elevator set functions
	//-----------------------------------------------------------------------------------------------------------------

	void set_ip(std::string ip){this->elevator_status.ip = ip;}

	void set_order_matrix(std::vector<std::vector <Queue_element> > *order_matrix_ptr);

	void set_order_matrix_ptr(std::vector<std::vector <Queue_element> > *order_matrix_ptr){this->order_matrix_ptr = order_matrix_ptr;}

	void set_role(Role role){this->elevator_status.role = role;}

	void set_dir(Dirn dir){this->elevator_status.dir = dir;}

	void set_floor(int floor){this->elevator_status.floor = floor;}

	void set_last_floor(int last_floor){this->elevator_status.last_floor = last_floor;}

	void set_current_state(State current_state){this->elevator_status.current_state = current_state;}

	void set_ID(int elevator_ID){this->elevator_status.elevator_ID = elevator_ID;}

	void set_out_of_order(bool out_of_order){this->elevator_status.out_of_order = out_of_order;}

	void set_online(bool online){this->elevator_status.online = online;}

	void set_status(Status &status){this->elevator_status = status;}
};