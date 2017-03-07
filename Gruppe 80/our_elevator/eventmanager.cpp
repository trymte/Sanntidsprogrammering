#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <unistd.h>
#include <deque>
#include <algorithm>

#include "eventmanager.h"
#include "timer.h"





bool check_buttons(Queue &my_queue){
	Order new_order;
	bool new_button_press = 0;
	for(int i=0; i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if (elev_get_button_signal((elev_button_type_t)j,i) && (my_queue.get_order_matrix()[i][j].active_button == 0)){
				new_order.floor = i;
				new_order.btn = (Button)j;
				new_button_press = 1;
				
				my_queue.add_order(new_order,-1); //Skal være -1
			}
		}
	}
	return new_button_press;
}

void set_all_lights(Queue &my_queue){
	for(int i =0;i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if(my_queue.get_order_matrix()[i][j].active_button == 1){
				elev_set_button_lamp((elev_button_type_t)j,i,1);
			}
			else
				elev_set_button_lamp((elev_button_type_t)j,i,0);
		}
	} 
}
 
 
void event_manager_main(Elevator *my_elevator, Queue &my_queue, Network &my_network){
//////////////////////////////////////////////////////////////////////////////// 
//Initializing
////////////////////////////////////////////////////////////////////////////////     
	std::cout << "Event manager initializing..." << std::endl; 
	elev_init();
	int input_poll_rate_ms = 25;
	while(elev_get_floor_sensor_signal() != 0){
		elev_set_motor_direction(DIRN_DOWN);
	}
	elev_set_motor_direction(DIRN_STOP); 
	elev_set_floor_indicator(0);

	//Få master/slave status fra network. Vente på dette, eller bare beholde init-status (MASTER) til master inntil videre?


	std::cout << "Event manager initialized" << std::endl;
/////////////////////////////////////////////////////////////////////////////////
 

	while(1){ //Går an å ha en switch/case som tar for seg hele main-koden. Og ta alle bolkene med kode inn i hver sin funksjon. Ryddigere?
		if (check_buttons(my_queue)){
		
			switch(my_elevator->get_elevator_status().role){
			case MASTER:
				std::cout << "Supervisor" << std::endl;
				sv_manage_order_matrix(my_network.get_elevators_ptr(), my_elevator->get_elevator_ID());
				break;

			case SLAVE:
				std::cout << "Send_message_packet" << std::endl;
				my_network.send_message_packet(SLAVE_SEND_ELEVATOR_INFORMATION, my_elevator->get_elevator_ID());
				break;
			}
	
		}

		//Check condition timer
		if((timer_timedOut())&& (get_timer_id() == TIMER_CONDITION_ID)){ //Går an å ha en event på dette. Blir kanskje litt mer ryddig?
			std::cout << "Elevator is out of order" << std::endl;
			my_elevator->set_elevator_out_of_order(1);
			timer_stop();

			my_queue.reset_orders(my_elevator->get_elevator_status());
			switch(my_elevator->get_elevator_status().role){
			case MASTER:
				//sv_manage_incomplete_order(my_elevator);
				break;

			case SLAVE:
				//Kall netverksfunksjon som sender elevator objekt til master.
				break;
			}
		} 

		//Check door timer
		if((timer_timedOut()) && (get_timer_id() == TIMER_DOOR_ID)){ 
			fsm_on_door_timeout(my_elevator,my_queue);
		}

		//Check order to be executed
		Order next_order = my_queue.get_next_order(my_elevator->get_elevator_ID());
		if (next_order.active_order == 1){ 
			fsm_execute_order(my_elevator,my_queue,next_order);
		}

		//Check floor arrival
		int current_floor = elev_get_floor_sensor_signal();
		my_elevator->set_elevator_floor(current_floor);
		if (elev_get_floor_sensor_signal() != -1){
			if(fsm_on_floor_arrival(my_elevator,my_queue,current_floor)){
				switch(my_elevator->get_elevator_role()){
					case MASTER:
						sv_manage_completed_order(my_elevator, my_elevator->get_elevator_ID());
						break;
					case SLAVE:
						my_network.send_message_packet(SLAVE_ORDER_COMPLETE, my_elevator->get_elevator_ID());
						break;
				}
				
			}
		}

		

	

//		std::cout << my_elevator.get_elevator_status().current_state << std::endl;      
		set_all_lights(my_queue);
		my_queue.write_order_matrix_to_file();
	 
		usleep(input_poll_rate_ms*1000);   
	}  
  
	   
 
  
}
/*
  
To do:
- Read/write ordermatrix to file
- Calculate cost
- Out of order -> Slette jobber med sin elevator id, deretter send elevator til master.

- Role --> Assign elevators to orders etc (inform_supervisor)
- Supervisor funksjoner
*/

/*
int my_network = 1;
int *my_elevator = &my_network;	

std::cout << "My_network = " << my_network << std::endl;
*my_elevator = 2;
std::cout << "My_elevator = " << *my_elevator << std::endl;
std::cout << "My_network = " << my_network << std::endl;
*/







