#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <unistd.h>
#include <deque>
#include <algorithm>
#include "eventmanager.h"


//-----------------------------------------------------------------------------------------------------------------------------------------
// Function to initialize elevator to floor 0
//-----------------------------------------------------------------------------------------------------------------------------------------

void elev_drive_to_init_floor(Elevator *my_elevator){
	while(elev_get_floor_sensor_signal() != 0)
		elev_set_motor_direction(DIRN_DOWN);
		my_elevator->set_current_state(MOVING);
	elev_set_motor_direction(DIRN_STOP); 
	elev_set_floor_indicator(0);
	my_elevator->set_out_of_order(0);
	my_elevator->set_current_state(IDLE);
	std::cout << "Elevator not out of order" << std::endl;

}

//--------------------------------------------------------------------------------------------------------------------------------
//		Local eventmanager functions which monitor hardware 
//--------------------------------------------------------------------------------------------------------------------------------

bool check_buttons(Elevator *my_elevator, Queue &my_queue){
	Order new_order;
	bool new_button_press = 0;
	for(unsigned int i=0; i<N_FLOORS;i++){
		for(unsigned int j=0;j<N_BUTTONS;j++){
			if (elev_get_button_signal((elev_button_type_t)j,i) && (my_queue.get_order_matrix()[i][j].active_button == 0)){
				new_order.floor = i;
				new_order.btn = (Button)j;
				new_button_press = 1;
				if (new_order.btn == B_Cab)
					my_queue.add_order(new_order,my_elevator->get_status().elevator_ID);
				else
					my_queue.add_order(new_order,-1);
			}
		}
	}
	return new_button_press;
}


void check_all_lights(Elevator *my_elevator, Queue &my_queue){
	for(unsigned int i =0;i<N_FLOORS;i++){
		//Set external lights if any order with correct elevator ID
		for(unsigned int j=0;j<N_BUTTONS-1;j++){
			if(my_queue.get_order_matrix()[i][j].active_button == 1){
				elev_set_button_lamp((elev_button_type_t)j,i,1);
			}
			else
				elev_set_button_lamp((elev_button_type_t)j,i,0);
		}
		//Set internal lights if any order
		if (my_queue.get_order_matrix()[i][(int)B_Cab].active_button == 1){//ee
			elev_set_button_lamp(BUTTON_COMMAND,i,1);
		}
		else{
			elev_set_button_lamp(BUTTON_COMMAND,i,0);
		}
	} 
}


void check_condition_timer(Elevator* my_elevator, Network &my_network, Queue &my_queue){
	if((timer_timed_out())&& (get_timer_id() == TIMER_CONDITION_ID)){ 
		std::cout << "Elevator is out of order" << std::endl;
		my_elevator->set_out_of_order(1);
		timer_stop();
		my_queue.reset_orders(my_elevator->get_status());
		switch(my_elevator->get_status().role){
			case MASTER:
				sv_manage_order_matrix(my_network.get_elevators(), my_elevator->get_status().elevator_ID);  
				my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_status().elevator_ID,"");
				break;
			case SLAVE:
				my_network.send_message_packet(SLAVE_ORDER_INCOMPLETE, my_elevator->get_status().elevator_ID, my_network.get_master_ip());
				break;
		}
		elev_drive_to_init_floor(my_elevator);
	} 
}


void check_door_timer(Elevator* my_elevator, Network &my_network, Queue &my_queue){
	if((timer_timed_out()) && (get_timer_id() == TIMER_DOOR_ID)){
		fsm_on_door_timeout(my_elevator,my_queue);
		switch(my_elevator->get_status().role){
			case MASTER:
				my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_status().elevator_ID,"");
				break;
			case SLAVE:
				my_network.send_message_packet(SLAVE_ORDER_COMPLETE, my_elevator->get_status().elevator_ID, my_network.get_master_ip());
				break;
		}
	}
}
 

void check_order_to_be_executed(Elevator* my_elevator, Queue &my_queue){
	Order next_order = my_queue.get_next_order(my_elevator->get_status().elevator_ID);
	if (next_order.active_order){ 
		fsm_execute_order(my_elevator,my_queue,next_order);
	}
}


void check_floor_arrival(Elevator* my_elevator, Queue &my_queue, Network &my_network){
	int current_floor = elev_get_floor_sensor_signal();
	my_elevator->set_floor(current_floor);
	if (current_floor != -1){
		my_elevator->set_last_floor(current_floor);
		if(fsm_on_floor_arrival(my_elevator,my_queue,current_floor)){
			switch(my_elevator->get_status().role){
				case MASTER:
					sv_manage_completed_order(my_elevator);
					sv_manage_order_matrix(my_network.get_elevators(),my_elevator->get_status().elevator_ID);
					my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_status().elevator_ID,"");
					break;
				case SLAVE:
					my_network.send_message_packet(SLAVE_ORDER_COMPLETE, my_elevator->get_status().elevator_ID, my_network.get_master_ip());
					break;
			}	
		}
	}
 }


//-----------------------------------------------------------------------------------------------------------------------------------------

void event_manager_main(Elevator *my_elevator, Network &my_network, Queue &my_queue){  
	int input_poll_rate_ms = 25;
	std::cout << "--------------------------------------------------------" << std::endl;  
	std::cout << "		Event manager initializing...			  " << std::endl; 
	elev_init();
	elev_drive_to_init_floor(my_elevator);
	std::cout << "		Event manager initialized" 	<< std::endl;
	std::cout << "--------------------------------------------------------" << std::endl; 
	my_queue.read_order_matrix_from_file();
	print_order_matrix(my_queue.get_order_matrix_ptr());
 	
	while(1){ 
		if (check_buttons(my_elevator, my_queue)){
			switch(my_elevator->get_status().role){
				case MASTER:
					sv_manage_order_matrix(my_network.get_elevators(),my_elevator->get_status().elevator_ID);
					my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_status().elevator_ID,"");
					break;
				case SLAVE:
					my_network.send_message_packet(SLAVE_SEND_ELEVATOR_INFORMATION, my_elevator->get_status().elevator_ID, my_network.get_master_ip());
					break;
				}
		}
		check_condition_timer(my_elevator, my_network, my_queue);

		check_door_timer(my_elevator, my_network, my_queue);
		
		check_order_to_be_executed(my_elevator, my_queue);
		
		check_floor_arrival(my_elevator, my_queue, my_network);

		check_all_lights(my_elevator,my_queue);

		my_queue.write_order_matrix_to_file();
	 
		usleep(input_poll_rate_ms*1000);   
	}  
}