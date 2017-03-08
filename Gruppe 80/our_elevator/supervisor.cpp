#include "supervisor.h"


void sv_manage_order_matrix(std::vector<Elevator*> elevators){	
	std::vector<std::vector<Queue_element> > temp = Queue::assign_elevators_to_orders(elevators);
	std::cout << "------------------------------------------------------------------------"<< std::endl;
	std::cout << "Global order matrix: " << std::endl;
	std::cout << "------------------------------------------------------------------------- " <<std::endl;
	print_order_matrix(&temp);

	for(unsigned int i = 0; i < N_ELEVATORS; i ++){
		elevators[i]->set_elevator_order_matrix(&temp);
	}
}


void sv_manage_completed_order(Elevator* elevator){
	//Remove order that elevator is done with.
	Status elevator_status = elevator->get_elevator_status();
	std::vector<std::vector<Queue_element> >* elevator_order_matrix_ptr;
	elevator_order_matrix_ptr = elevator->get_order_matrix_ptr();

	//Removes all orders on current floor with correct elevator_ID
	for(int i=0;i<N_BUTTONS;i++){
		if ((*elevator_order_matrix_ptr)[elevator_status.floor][i].elevator_ID == elevator_status.floor){
			(*elevator_order_matrix_ptr)[elevator_status.floor][i].active_button = 0;
			(*elevator_order_matrix_ptr)[elevator_status.floor][i].elevator_ID = -1;
		}
	}
	elevator_order_matrix_ptr = NULL;
}
	