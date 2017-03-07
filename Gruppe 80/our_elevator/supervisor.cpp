#include "supervisor.h"


void sv_manage_order_matrix(std::vector<Elevator> *elevators, int master_elevator_ID){	
	std::vector<std::vector<Queue_element> > temp = Queue::assign_elevators_to_orders(*elevators);
	for(unsigned int i = 0; i < N_ELEVATORS; i ++){
		(*elevators)[i].set_elevator_order_matrix(&temp);
	}
}


void sv_manage_completed_order(Elevator* elevator, int master_elevator_ID){
	//Remove order that elevator is done with.
	Status elevator_status = elevator->get_elevator_status();
	
	std::vector<std::vector<Queue_element> > elevator_order_matrix;
	elevator_order_matrix = *elevator->get_order_matrix_ptr();

	//Removes all orders on current floor with correct elevator_ID
	for(int i=0;i<N_BUTTONS;i++){
		if (elevator_order_matrix[elevator_status.floor][i].elevator_ID == elevator_status.floor){
			//Kan også bruke Queue::remove_order(), men må da ha et ordre objekt... unødvendige linjer kode? Jeg er enig, bare ha det slik. -Morten
			elevator_order_matrix[elevator_status.floor][i].active_button = 0;
			elevator_order_matrix[elevator_status.floor][i].elevator_ID = -1;
		}
	}
}


void sv_manage_incomplete_order(Elevator* elevator, int master_elevator_ID){ //Blir kalt dersom det oppdages et elevator objekt med out_of_order. Lage en\
 funksjon i network sin main loop som sjekker dette, og kaller funksjonen?
	//Queue::reset_orders(*elevator.get_order_matrix_ptr(),elevator.get_elevator_status());

	//Queue reset orders
	//Assign elevators to orders
	//Distribute order matrix
}
