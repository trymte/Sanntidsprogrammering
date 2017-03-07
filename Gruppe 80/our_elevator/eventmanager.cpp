#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <unistd.h>
#include <deque>
#include <algorithm>

#include "eventmanager.h"






bool check_buttons(int &my_elevator_ID, Queue &my_queue){
	Order new_order;
	bool new_button_press = 0;
	for(int i=0; i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if (elev_get_button_signal((elev_button_type_t)j,i) && (my_queue.get_order_matrix()[i][j].active_button == 0)){
				std::cout << "Button pressed" << std::endl;
				new_order.floor = i;
				new_order.btn = (Button)j;
				new_button_press = 1;
				
				if (new_order.btn == B_Cab)
					my_queue.add_order(new_order,my_elevator_ID);
				else
					my_queue.add_order(new_order,-1);
			}
		}
	}
	return new_button_press;
}

void set_all_lights(int &my_elevator_ID, Queue &my_queue){
	for(int i =0;i<N_FLOORS;i++){
		//Set external lights
		for(int j=0;j<N_BUTTONS-1;j++){
			if(my_queue.get_order_matrix()[i][j].active_button == 1)
				elev_set_button_lamp((elev_button_type_t)j,i,1);
			else
				elev_set_button_lamp((elev_button_type_t)j,i,0);
		}

		//Set cab lights
		if (i == (int)B_Cab){
			if((my_queue.get_order_matrix()[i][N_BUTTONS-1].active_button == 1) && (my_queue.get_order_matrix()[i][N_BUTTONS-1].elevator_ID == my_elevator_ID))
				elev_set_button_lamp((elev_button_type_t)(N_BUTTONS-1),i,1);
			else
				elev_set_button_lamp((elev_button_type_t)(N_BUTTONS-1),i,0);
		}
	} 
}


void check_condition_timer(int &my_elevator_ID, Network &my_network, Queue &my_queue){
	if((timer_timedOut())&& (get_timer_id() == TIMER_CONDITION_ID)){ 
		std::cout << "Elevator is out of order" << std::endl;
		(*my_network.get_elevators_ptr())[my_elevator_ID].set_elevator_out_of_order(1);
		timer_stop();

		my_queue.reset_orders((*my_network.get_elevators_ptr())[my_elevator_ID].get_elevator_status());
		switch((*my_network.get_elevators_ptr())[my_elevator_ID].get_elevator_status().role){
			case MASTER:
				//sv_manage_order_matrix(my_network.get_elevators_ptr());  //my_elevator);
				my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, (*my_network.get_elevators_ptr())[my_elevator_ID].get_elevator_ID());
				break;
			case SLAVE:
				my_network.send_message_packet(SLAVE_ORDER_INCOMPLETE, (*my_network.get_elevators_ptr())[my_elevator_ID].get_elevator_ID());
				break;
		}
	} 
}

void check_door_timer(int &my_elevator_ID,Network &my_network, Queue &my_queue){
	if((timer_timedOut()) && (get_timer_id() == TIMER_DOOR_ID)){ 
		fsm_on_door_timeout(my_elevator_ID,my_network,my_queue);
	}
}
 
void check_order_to_be_executed(int &my_elevator_ID, Network &my_network ,Queue &my_queue){
	Order next_order = my_queue.get_next_order(my_elevator_ID);
		if (next_order.active_order == 1){ 
			fsm_execute_order(my_elevator_ID,my_network,my_queue,next_order);
		}
}

void check_floor_arrival(int &my_elevator_ID, Queue &my_queue, Network &my_network){
	int current_floor = elev_get_floor_sensor_signal();
	(*my_network.get_elevators_ptr())[my_elevator_ID].set_elevator_floor(current_floor);
	if (elev_get_floor_sensor_signal() != -1){
		if(fsm_on_floor_arrival(my_elevator_ID,my_network,my_queue,current_floor)){
			switch((*my_network.get_elevators_ptr())[my_elevator_ID].get_elevator_role()){
				case MASTER:
					std::cout << "My elevator:" << std::endl;
					sv_manage_completed_order(my_elevator_ID,my_network.get_elevators_ptr());
					sv_manage_order_matrix(my_network.get_elevators_ptr());
					break;
				case SLAVE:
					my_network.send_message_packet(SLAVE_ORDER_COMPLETE, my_elevator_ID);
					break;
			}	
		}
	}
 }


void event_manager_main(int &my_elevator_ID, Queue &my_queue, Network &my_network){    
	std::cout << "------------------------------------------------" << std::endl; 

//////////////////////////////////////////////////////////////////////////////// 
//Initializing
////////////////////////////////////////////////////////////////////////////////     

	std::cout << "Event manager initializing..." << std::endl; 
	std::cout << "------------------------------------------------" << std::endl; 
	elev_init();

	int input_poll_rate_ms = 25;
	while(elev_get_floor_sensor_signal() != 0)
		elev_set_motor_direction(DIRN_DOWN);
	elev_set_motor_direction(DIRN_STOP); 
	elev_set_floor_indicator(0);

	std::cout << "Event manager initialized" << std::endl;
/////////////////////////////////////////////////////////////////////////////////
 

	while(1){ 
		if (check_buttons(my_elevator_ID, my_queue)){
			switch((*my_network.get_elevators_ptr())[my_elevator_ID].get_elevator_status().role){//} my_elevator->get_elevator_status().role){
			case MASTER:
				std::cout << "Supervisor" << std::endl;
				sv_manage_order_matrix(my_network.get_elevators_ptr());
				break;
			case SLAVE:
				std::cout << "Send_message_packet" << std::endl;
				my_network.send_message_packet(SLAVE_SEND_ELEVATOR_INFORMATION, my_elevator_ID);
				break;
			}
		}
		check_condition_timer(my_elevator_ID, my_network, my_queue);

		check_door_timer(my_elevator_ID,my_network, my_queue);
		
		check_order_to_be_executed(my_elevator_ID ,my_network ,my_queue);
		
		check_floor_arrival(my_elevator_ID, my_queue, my_network);

//		std::cout << my_elevator.get_elevator_status().current_state << std::endl;      

		set_all_lights(my_elevator_ID,my_queue);

		my_queue.write_order_matrix_to_file();
	 
		usleep(input_poll_rate_ms*1000);   
	}  
}








