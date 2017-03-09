#include "supervisor.h"


void sv_manage_order_matrix(std::vector<Elevator*> elevators, int elevator_ID){	
	std::vector<std::vector<Queue_element> > temp = Queue::assign_elevators_to_orders(elevators,elevator_ID);
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
	std::vector<std::vector<Queue_element> > elevator_order_matrix = *elevator->get_order_matrix_ptr();
	std::cout << "Completed order elevator before delete: " << std::endl;
	elevator->print_elevator();
	

	//Removes all orders on current floor with correct elevator_ID
	for(int i=0;i<N_BUTTONS;i++){
		if(elevator_status.floor != -1){
			if (elevator_order_matrix[elevator_status.floor][i].elevator_ID == elevator_status.elevator_ID){
			elevator_order_matrix[elevator_status.floor][i].active_button = 0;
			elevator_order_matrix[elevator_status.floor][i].elevator_ID = -1;
			std::cout << "Deleted" << std::endl;
			}
		}
	}
	elevator->set_elevator_order_matrix(&elevator_order_matrix);
	std::cout << "Completed order elevator after delete: " << std::endl;
	elevator->print_elevator();
}