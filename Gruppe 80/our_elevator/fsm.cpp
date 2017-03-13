#include "fsm.h"

//-----------------------------------------------------------------------------------------------------------------
//				Local functions used only in fsm
//-----------------------------------------------------------------------------------------------------------------


bool requests_above(Elevator *my_elevator, Queue &my_queue,int current_floor){
	for(unsigned int i = current_floor + 1; i<N_FLOORS; i++){
		for(unsigned int j=0; j<N_BUTTONS; j++){
			if ((my_queue.get_order_matrix()[i][j].active_button == 1) && (my_queue.get_order_matrix()[i][j].elevator_ID == my_elevator->get_status().elevator_ID))
				return 1;
		}
	}
	return 0;
}


bool requests_below(Elevator *my_elevator, Queue &my_queue, int current_floor){
	for(int i=0; i<current_floor; i++){
		for(unsigned int j=0; j<N_BUTTONS; j++){
			if ((my_queue.get_order_matrix()[i][j].active_button == 1) && (my_queue.get_order_matrix()[i][j].elevator_ID == my_elevator->get_status().elevator_ID))
				return 1;
		}
	}
	return 0;
}


bool requests_should_stop(Elevator *my_elevator, Queue &my_queue){
	int current_floor = my_elevator->get_status().floor;
	switch(my_elevator->get_status().dir){
	case D_Down:
		return
			((my_queue.get_order_matrix()[current_floor][(int)B_HallDown].active_button) && 
			 (my_queue.get_order_matrix()[current_floor][(int)B_HallDown].elevator_ID ==  my_elevator->get_status().elevator_ID)) ||
			
			((my_queue.get_order_matrix()[current_floor][(int)B_Cab].active_button) &&
			 (my_queue.get_order_matrix()[current_floor][(int)B_Cab].elevator_ID ==  my_elevator->get_status().elevator_ID))      ||

			!(requests_below(my_elevator, my_queue, current_floor));

	case D_Up:
		return
			((my_queue.get_order_matrix()[current_floor][(int)B_HallUp].active_button) && 
			 (my_queue.get_order_matrix()[current_floor][(int)B_HallUp].elevator_ID ==  my_elevator->get_status().elevator_ID)) ||
			
			((my_queue.get_order_matrix()[current_floor][(int)B_Cab].active_button) &&
			 (my_queue.get_order_matrix()[current_floor][(int)B_Cab].elevator_ID ==  my_elevator->get_status().elevator_ID))    ||

			!(requests_above(my_elevator, my_queue, current_floor));

	default:
		return 0;
	}
}

void open_door(){
	elev_set_door_open_lamp(1);
	timer_start(DOOR_TIME_S, TIMER_DOOR_ID);
}


//-----------------------------------------------------------------------------------------------------------------
//									fsm executing functions
//-----------------------------------------------------------------------------------------------------------------


void fsm_execute_order(Elevator *my_elevator, Queue &my_queue, Order &order){
	int current_floor = my_elevator->get_status().floor;

	if(my_elevator->get_status().current_state == IDLE){
		if(current_floor > order.floor){
			timer_start(TIME_CONDITION_S,TIMER_CONDITION_ID);
			elev_set_motor_direction(DIRN_DOWN);
			my_elevator->set_dir(D_Down);
			my_elevator->set_current_state(MOVING);
		}
		else{
			timer_start(TIME_CONDITION_S,TIMER_CONDITION_ID);
			elev_set_motor_direction(DIRN_UP);
			my_elevator->set_dir(D_Up);
			my_elevator->set_current_state(MOVING);
		}
		
	}
}


bool fsm_on_floor_arrival(Elevator *my_elevator,Queue &my_queue, int current_floor){
	bool stopped = false;
	elev_set_floor_indicator(current_floor);
	my_elevator->set_floor(current_floor);
	switch(my_elevator->get_status().current_state){
		case MOVING:
			if (requests_should_stop(my_elevator, my_queue)){
				stopped = true;			
				elev_set_motor_direction(DIRN_STOP);
				if (get_timer_id() == TIMER_CONDITION_ID)
					timer_stop();

				if (get_timer_id() == 0){
					open_door();
				}
				my_elevator->set_dir(D_Stop);
	   			my_elevator->set_current_state(DOOR_OPEN);

	   			if (requests_should_stop(my_elevator, my_queue)){
	   				my_elevator->set_out_of_order(0);
	   			}
			}
			break;
			
		case IDLE:
			for(unsigned int i=0;i<N_BUTTONS;i++){
				if ((my_queue.get_order_matrix()[current_floor][i].active_button == 1) && 
					(my_queue.get_order_matrix()[current_floor][i].elevator_ID == my_elevator->get_status().elevator_ID)){
					stopped = true;
					
					if (get_timer_id() == TIMER_CONDITION_ID){
						timer_stop();
					}
					if (get_timer_id() == 0){
						open_door();
					}
					my_elevator->set_dir(D_Stop);
		   			my_elevator->set_current_state(DOOR_OPEN);

		   			if (requests_should_stop(my_elevator, my_queue)){
		   				my_elevator->set_out_of_order(0);
		   			}

		   			if ((my_queue.get_order_matrix()[current_floor][(int)B_Cab].active_button) && 
		   				(my_queue.get_order_matrix()[current_floor][(int)B_Cab].elevator_ID == my_elevator->get_status().elevator_ID)){
		   				Order cab_order_rmv;
		   				cab_order_rmv.active_order = 1;
		   				cab_order_rmv.floor = current_floor;
		   				cab_order_rmv.btn = Button(B_Cab);
		   				my_queue.remove_order(cab_order_rmv);
		   			}
				}
			}
			break;
	}
	return stopped;
}

void fsm_on_door_timeout(Elevator *my_elevator,Queue &my_queue){
	int current_floor = elev_get_floor_sensor_signal();
	my_elevator->set_current_state(IDLE);
	elev_set_door_open_lamp(0);
	if(get_timer_id() == TIMER_DOOR_ID)
		timer_stop();

	Order order_to_be_removed;
	for(unsigned int i=0;i<N_BUTTONS;i++){
		if((my_queue.get_order_matrix()[current_floor][i].active_button == 1) && 
			(my_queue.get_order_matrix()[current_floor][i].elevator_ID == my_elevator->get_status().elevator_ID)){
			order_to_be_removed.floor = current_floor;
			order_to_be_removed.btn = (Button)i;
			my_queue.remove_order(order_to_be_removed);
		}
	}
}