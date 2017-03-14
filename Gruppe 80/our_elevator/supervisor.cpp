#include "supervisor.h"

void sv_manage_order_matrix(std::vector<Elevator*> elevators, int elevator_ID){	
	std::vector<std::vector<Queue_element> > new_order_matrix = Queue::assign_elevators_to_orders(elevators,elevator_ID);
	for(unsigned int i = 0; i < N_ELEVATORS; i ++){
		elevators[i]->set_order_matrix(&new_order_matrix);
	}
}

void sv_manage_incompleted_and_completed_orders(Elevator* elevator){
	Status elevator_status = elevator->get_status();
	std::vector<std::vector<Queue_element> > elevator_order_matrix = *elevator->get_order_matrix_ptr();
	
	//Reset all orders if the elevator is offline
	if (elevator_status.online == 0){
		Queue::reset_orders(elevator_order_matrix, elevator_status);
	}

	//Removes all orders on current floor with correct elevator_ID if completed order
	else{
		for(unsigned int i=0;i<N_BUTTONS;i++){
			if (elevator_status.floor != -1){
				if (elevator_order_matrix[elevator_status.floor][i].elevator_ID == elevator_status.elevator_ID){
					elevator_order_matrix[elevator_status.floor][i].active_button = 0;
					elevator_order_matrix[elevator_status.floor][i].elevator_ID = -1;
				}
			}
		}
	}
	elevator->set_order_matrix(&elevator_order_matrix);
}