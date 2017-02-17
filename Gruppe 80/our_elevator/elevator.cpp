#include "elevator.h"




Elevator::Elevator(): order_matrix_ptr(NULL)
{
	elevator_status.dir = D_Stop;
	elevator_status.floor = -1;
	elevator_status.elevator_ID = -1;
	elevator_status.out_of_order = 1;
}

Elevator::Elevator(Status elevator_status): elevator_status(elevator_status)
{
	//order_matrix_ptr = Queu::queue_get_order_matrix();
	//order_matrix_ptr = queue1.queue_get_order_matrix();
}

Elevator::Elevator(const Elevator &elevator): elevator_status(elevator.elevator_status)
{
	order_matrix_ptr = new Queue_element*[N_FLOORS];
	for(int i = 0; i < N_BUTTONS; i++){
		order_matrix_ptr[i] = new Queue_element[N_BUTTONS];
	}
	for(int j = 0; j < N_FLOORS; j++){
		for(int k = 0; k < N_BUTTONS; k++){
			order_matrix_ptr[j][k] = elevator.order_matrix_ptr[j][k];
		}
	}
}


Elevator::~Elevator(){
	if(order_matrix_ptr != NULL){
		for(int i = 0; i < N_FLOORS; i++){
			delete order_matrix_ptr[i];
		}
		delete [] order_matrix_ptr;
	}
	
}

