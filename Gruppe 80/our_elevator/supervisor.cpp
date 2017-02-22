#include "supervisor.h"


void manage_order_matrix(std::vector<Elevator> &elevators){
	
	std::vector<Queue_element> order_matrix_merged[N_FLOORS][N_BUTTONS];
	std::vector<Elevator>::iterator it;

	for(it = elevators.begin();it!=elevators.end();++it){ 
		order_matrix_merged = Queue::queue_merge_order_matrices(order_matrix_merged, it->get_order_matrix());
	}

	for(it = elevators.begin();it!=elevators.end();++it){
		it->set_order_matrix(order_matrix_merged);
	}

	order_matrix_merged = Queue::queue_assign_elevators_to_orders(elevators);
}


void manage_completed_order(Elevator &elevator){
	//Remove order that elevator is done with.
	Status elevator_status = elevator.get_elevator_status();
	
}


void manage_incomplete_order(Elevator &elevator){

}