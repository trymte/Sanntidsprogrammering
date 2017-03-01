#include "elevator.h"
#include "queue.h"
#include "const_struct_def.h"
#include "fsm.h"
#include "driver/timer.h"


void open_door(){
	std::cout << "Door open" << std::endl;
	elev_set_door_open_lamp(1);
	timer_door_start(DOOR_TIME_S);
}

void fsm_execute_order(Elevator &my_elevator, Queue &my_queue, Order &order){ //Status &status,Order &order) 
	int current_floor = my_elevator.get_elevator_status().floor;
	State current_state = my_elevator.get_elevator_status().current_state;

//	timer_condition_start(CONDITION_TIME_S);

	switch(current_state){
		case MOVING:
			if(current_floor == order.floor){
				fsm_on_floor_arrival(my_elevator,my_queue);
			}

			break;

   		case IDLE:
   			if(current_floor == order.floor){
   				fsm_on_floor_arrival(my_elevator,my_queue);
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
// 			timer_condition_stop();
			
   		}
	}
}


void fsm_on_door_timeout(Elevator &my_elevator,Queue &my_queue){
	int current_floor = elev_get_floor_sensor_signal();
	my_elevator.set_elevator_current_state(IDLE);
	elev_set_door_open_lamp(0);
	timer_door_stop();

	Order order_to_be_removed;
	for(int i=0;i<N_BUTTONS;i++){
		if((my_queue.get_order_matrix()[current_floor][i].active_button == 1) && (my_queue.get_order_matrix()[current_floor][i].elevator_ID == elevator_ID)){//Readressere hvor elevator_ID kommer fra.
			order_to_be_removed.floor = current_floor;
			order_to_be_removed.btn = (Button)i;
			my_queue.remove_order(order_to_be_removed);
		}
	}
}

