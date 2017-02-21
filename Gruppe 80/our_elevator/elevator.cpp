#include "elevator.h"



Elevator::Elevator(): order_matrix_ptr(0)
{
	elevator_status.dir = D_Stop;
	elevator_status.floor = -1;
	elevator_status.elevator_ID = -1;
	elevator_status.out_of_order = 1;
}

Elevator::Elevator(Status elevator_status, std::vector<std::vector <Queue_element> > *order_matrix_ptr): elevator_status(elevator_status)
{
	this->order_matrix_ptr = new std::vector<std::vector <Queue_element> >;
	this->order_matrix_ptr = &order_matrix_ptr;
}

Elevator::Elevator(const Elevator &elevator): elevator_status(elevator.elevator_status)
{
	std::vector<std::vector <Queue_element> > temp[N_FLOORS][N_BUTTONS];
}


Elevator::~Elevator(){
	if(order_matrix_ptr != 0){
		delete [] order_matrix_ptr;
		order_matrix_ptr = 0;
	}
}


//--------------------------------------------------------------------------------------------------
//Public functions
//--------------------------------------------------------------------------------------------------

void Elevator::set_elevator_order_matrix_ptr(std::vector<std::vector <Queue_element> > *order_matrix_ptr){
	if(this->order_matrix_ptr == 0){
		this->order_matrix_ptr = new Queue_element*[N_FLOORS];
		for(int i = 0; i < N_BUTTONS; i++){
			this->order_matrix_ptr[i] = new Queue_element[N_BUTTONS];
		}
	}
	for(int j = 0; j < N_FLOORS; j++){
		for(int k = 0; k < N_BUTTONS; k++){
			this->order_matrix_ptr[j][k] = (*order_matrix_ptr)[j][k];
		}
	}
}

Elevator& Elevator::operator=(const Elevator &rhs){
	this->elevator_status = rhs.elevator_status;
	if(this->order_matrix_ptr == 0){
		this->order_matrix_ptr = new Queue_element*[N_FLOORS];
		for(int i = 0; i < N_BUTTONS; i++){
			this->order_matrix_ptr[i] = new Queue_element[N_BUTTONS];
		}
	}
	for(int j = 0; j < N_FLOORS; j++){
		for(int k = 0; k < N_BUTTONS; k++){
			this->order_matrix_ptr[j][k] = rhs.order_matrix_ptr[j][k];
		}
	}
	return *this;
}
