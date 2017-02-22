#include "supervisor.h"


void manage_order_matrix(std::vector<Elevator> &elevators){	
	distribute_order_matrix(Queue::queue_assign_elevators_to_orders(elevators));
}


void manage_completed_order(Elevator &elevator){
	//Remove order that elevator is done with.
	Status elevator_status = elevator.get_elevator_status();
	//elevator->get_order_matrix_ptr()
	
}


void manage_incomplete_order(Elevator &elevator){

}