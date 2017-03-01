#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <unistd.h>
#include <deque>
#include <algorithm>

#include "eventmanager.h"
#include "driver/timer.h"

//Hvor skal denne?
int elevator_ID = 1;


bool check_buttons(Queue &my_queue){
	Order new_order;
	bool new_button_press = 0;
	for(int i=0; i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if (elev_get_button_signal((elev_button_type_t)j,i) && (my_queue.get_order_matrix()[i][j].active_button == 0)){
				new_order.floor = i;
				new_order.btn = (Button)j;
				new_button_press = 1;
				
				my_queue.add_order(new_order,1); //Skal være -1
				my_queue.print_order_matrix(); //Kan fjernes
			}
		}
	}
	return new_button_press;
}

void set_all_lights(Queue &my_queue){
	//Må lages, alternativt tenne lysene underveis?
	//Kan lese fra queue hvilke betjeningsknapper som skal lyse.


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

void open_door(){
	std::cout << "Door open" << std::endl;
	elev_set_door_open_lamp(1);
	//if (timer_started != 1)
		//timer_start(DOOR_TIME_S);
}

void fsm_execute_order(Elevator &my_elevator, Queue &my_queue, Order &order){ //Status &status,Order &order) 
	int current_floor = my_elevator.get_elevator_status().floor;
	State current_state = my_elevator.get_elevator_status().current_state;

	switch(current_state){
		case MOVING:

			if(current_floor == order.floor){	//Stop because the order to be executed is done.
	   				elev_set_motor_direction(DIRN_STOP);
	   				open_door();
	   				my_elevator.set_elevator_dir(D_Stop);
	   				my_elevator.set_elevator_current_state(DOOR_OPEN);
	   				my_elevator.set_elevator_floor(elev_get_floor_sensor_signal());
	   				my_queue.remove_order(order);
	   			} 

			break;

   		case IDLE:

   			if(current_floor == order.floor){
   				elev_set_motor_direction(DIRN_STOP);
   				open_door();
   				my_elevator.set_elevator_dir(D_Stop);
	   			my_elevator.set_elevator_current_state(DOOR_OPEN);
	   			my_queue.remove_order(order);

   			}

   			else if(current_floor > order.floor){
   				elev_set_motor_direction(DIRN_DOWN);
   				my_elevator.set_elevator_dir(D_Down);
	   			my_elevator.set_elevator_current_state(MOVING);
   				
   			}
   			
   			else{
   				elev_set_motor_direction(DIRN_UP);
   				my_elevator.set_elevator_dir(D_Up);
	   			my_elevator.set_elevator_current_state(MOVING);
   			}
   			
   			break;


   		default:
   			std::cout << "Default" << std::endl;
   			//Waiting for door to close...
   			break;
	}
}


void fsm_on_floor_arrival(Elevator &my_elevator,Queue &my_queue){
	int current_floor = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(current_floor);
	my_elevator.set_elevator_floor(current_floor);

	for(int i=0;i<N_BUTTONS;i++){
		if ((my_queue.get_order_matrix()[current_floor][i].active_button == 1) && (my_queue.get_order_matrix()[current_floor][i].elevator_ID == elevator_ID)){ //Readressere hvor elevator_ID kommer fra.
			elev_set_motor_direction(DIRN_STOP);
			open_door();
			my_elevator.set_elevator_dir(D_Stop);
   			my_elevator.set_elevator_current_state(DOOR_OPEN);
   			Order order_to_be_removed;
   			order_to_be_removed.floor = current_floor;
   			order_to_be_removed.btn = (Button)i;
   			my_queue.remove_order(order_to_be_removed);
   		}
	}
}


void fsm_on_door_timeout(Elevator &my_elevator,Queue &my_queue){
	int current_floor = elev_get_floor_sensor_signal();
	my_elevator.set_elevator_current_state(IDLE);
	elev_set_door_open_lamp(0);
	//timer_stop();

	Order order_to_be_removed;
	for(int i=0;i<N_BUTTONS;i++){
		if((my_queue.get_order_matrix()[current_floor][i].active_button == 1) && (my_queue.get_order_matrix()[current_floor][i].elevator_ID == elevator_ID)){//Readressere hvor elevator_ID kommer fra.
			order_to_be_removed.floor = current_floor;
			order_to_be_removed.btn = (Button)i;
			my_queue.remove_order(order_to_be_removed);
		}
	}
}



void event_manager_main(Elevator &my_elevator, Queue &my_queue){
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

	//Blir gjort i main
	my_elevator.set_elevator_current_state(IDLE);
	my_elevator.set_elevator_floor(0);
	my_elevator.set_elevator_dir(D_Stop);
	elev_set_floor_indicator(0);
	//
	
	std::cout << "Event manager initialized" << std::endl;
/////////////////////////////////////////////////////////////////////////////////


	while(1){
		
		if (check_buttons(my_queue)){
			//inform_supervisor(my_elevator);
		}

		Order next_order = my_queue.get_next_order(elevator_ID);
		//std::cout << "Floor: " << next_order.floor << "\t btn: " << next_order.btn << std::endl;
		//std::cout << my_elevator.get_elevator_status().current_state << std::endl;
		if (next_order.active_order == 1){//!((next_order.floor == 0) && (next_order.btn == B_HallDown))){ 
			fsm_execute_order(my_elevator,my_queue,next_order);
		}



		
		my_elevator.set_elevator_floor(elev_get_floor_sensor_signal());
		if (elev_get_floor_sensor_signal() != -1){
			fsm_on_floor_arrival(my_elevator,my_queue);
		}


		//Check timer if timedout
	//	if(timer_timedOut()){
			//fsm_on_door_timeout;
	//		timer_stop();
	//	}
		//Midlertidig inntil timer fungerer
		if((Button)my_elevator.get_elevator_status().current_state == DOOR_OPEN){
			fsm_on_door_timeout(my_elevator,my_queue);
		}


		set_all_lights(my_queue);



		//usleep(input_poll_rate_ms*1000);
	}
}



/*
To do:
- Ignorere knappetrykk OPP når dir = ned --> get_next_order bør sjekke retning på heisen for å avgjøre hvilken ordre den skal returnere.
- Timer
- Role --> Assign elevators to orders etc (inform_supervisor)
- Timer for elevator out of order
- Kan my_elevator og my_queue legges i en header fil slik at man slipper callbyreference over alt?
*/







