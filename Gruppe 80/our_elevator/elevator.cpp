#include "elevator.h"



Elevator::Elevator(): order_matrix_ptr(NULL), order_matrix_ptr_count(0)
{
	get_my_ipaddress(elevator_status.ip);
	elevator_status.role = SLAVE;
	elevator_status.dir = D_Stop;
	elevator_status.floor = -1;
	elevator_status.last_floor = -1;
	elevator_status.elevator_ID = -1;
	elevator_status.out_of_order = 1;
	elevator_status.online = 1;
}


Elevator::Elevator(Status elevator_status): elevator_status(elevator_status), order_matrix_ptr_count(0)
{
	std::vector<std::vector <Queue_element> > temp = init_twoD_vector();
	this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	*this->order_matrix_ptr = temp;
}


Elevator::Elevator(Status elevator_status, std::vector<std::vector <Queue_element> > *order_matrix_ptr): elevator_status(elevator_status)
{
	order_matrix_ptr_count += 1;
	this->order_matrix_ptr = order_matrix_ptr;
}


Elevator::Elevator(const Elevator &elevator): elevator_status(elevator.elevator_status)
{
	this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	*this->order_matrix_ptr = *elevator.order_matrix_ptr;
}


Elevator::~Elevator()
{
	if(order_matrix_ptr != NULL){
		if(order_matrix_ptr_count > 1){
			order_matrix_ptr_count -= 1;
		} else{
			delete order_matrix_ptr;
		}
		order_matrix_ptr = NULL;

	}
}


//--------------------------------------------------------------------------------------------------
//Public functions
//--------------------------------------------------------------------------------------------------


Elevator& Elevator::operator=(const Elevator &rhs)
{
	this->elevator_status = rhs.elevator_status;
	if(this->order_matrix_ptr == NULL){
		this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
	}
	*this->order_matrix_ptr = *order_matrix_ptr;
	return *this;
}


void Elevator::print_elevator()
{
	std::cout << "Elevator ip : " << elevator_status.ip << std::endl;
	std::cout << "Elevator Role : " << elevator_status.role << std::endl;
	std::cout << "Elevator id : " << elevator_status.elevator_ID << std::endl;
	std::cout << "Elevator current state: " << elevator_status.current_state << std::endl;
	std::cout << "Elevator floor : " << elevator_status.floor << std::endl;
	std::cout << "Elevator last floor : " << elevator_status.last_floor << std::endl;
	std::cout << "Elevator direction : " << elevator_status.dir << std::endl;
	std::cout << "Elevator out_of_order : " << elevator_status.out_of_order << std::endl;
	std::cout << "Elevator online : " << elevator_status.online << std::endl;
	print_order_matrix(order_matrix_ptr);
}

void Elevator::set_order_matrix(std::vector<std::vector <Queue_element> > *order_matrix_ptr)
{
	if(this->order_matrix_ptr == NULL){
		this->order_matrix_ptr = new std::vector<std::vector<Queue_element> >;
		*this->order_matrix_ptr = *order_matrix_ptr;
	} else{
		std::vector<std::vector <Queue_element> > temp = init_twoD_vector();
		for(unsigned int i = 0; i < N_FLOORS;i++){
			for(unsigned int j = 0; j < N_BUTTONS; j++){

				if(j == 2){
					temp[i][j] = (*this->order_matrix_ptr)[i][j];
				} else{
					temp[i][j] = (*order_matrix_ptr)[i][j];
				}
			}
		}
		*this->order_matrix_ptr = temp;
	}
}