#include "elevator.h"



Elevator::Elevator(): order_matrix_ptr(NULL)
{
//	get_my_ipaddress(elevator_status.ip);
	elevator_status.dir = D_Stop;
	elevator_status.floor = -1;
	elevator_status.elevator_ID = -1;
	elevator_status.out_of_order = 1;
}

Elevator::Elevator(Status elevator_status, std::vector<std::vector <Queue_element> > *order_matrix_ptr): elevator_status(elevator_status)
{
	this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	*this->order_matrix_ptr = *order_matrix_ptr;
}

Elevator::Elevator(const Elevator &elevator): elevator_status(elevator.elevator_status)
{
	this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	*this->order_matrix_ptr = *elevator.order_matrix_ptr;
}


Elevator::~Elevator(){
	if(order_matrix_ptr != 0){
		delete order_matrix_ptr;
		order_matrix_ptr = 0;
	}
}


//--------------------------------------------------------------------------------------------------
//Public functions
//--------------------------------------------------------------------------------------------------

void Elevator::set_elevator_order_matrix(std::vector<std::vector <Queue_element> > *order_matrix_ptr){
	if(this->order_matrix_ptr == 0){
		this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	}
	*this->order_matrix_ptr = *order_matrix_ptr;
}

Elevator& Elevator::operator=(const Elevator &rhs){
	this->elevator_status = rhs.elevator_status;
	if(this->order_matrix_ptr == 0){
		this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	}
	*this->order_matrix_ptr = *order_matrix_ptr;
	return *this;
}




//------------------------------------------------------------------------------------------------------------
//Others
//