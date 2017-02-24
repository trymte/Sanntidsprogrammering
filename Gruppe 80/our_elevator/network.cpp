#include "network.h"


Network::Network(){
	Elevator_online temp_elev_online;
	temp_elev_online.online = false;
	Elevator elev_temp;
	for(int i = 0; i < N_ELEVATORS ; i++){
		elevators.push_back(elev_temp);
		elevators[i].set_elevator_ID(i);
		elevators_online.push_back(temp_elev_online);
		elevators_online[i].elevator_ID = i;
	}
}

//--------------------------------------------------------------------------------------------------
//Private functions
//----------------------------------------------------------------------------------------------------

Elevator Network::messagestring_to_elevator_object(std::string &messagestring){
	Elevator temp_elevator;
	std::vector<std::string> result;
	std::string order_matrix_string;
	std::stringstream ss1(messagestring);
	std::string word;
	while(std::getline(ss1,word, ':')){
		result.push_back(word);
	}

	temp_elevator.set_elevator_ID(atoi(result[0].c_str()));
	switch(atoi(result[1].c_str())){
		case 0:
			temp_elevator.set_elevator_dir(D_Stop);
			break;
		case 1:
			temp_elevator.set_elevator_dir(D_Up);
			break;
		case -1:
			temp_elevator.set_elevator_dir(D_Down);
			break;
	}
	temp_elevator.set_elevator_floor(atoi(result[2].c_str()));
	if(result[3] == "0"){
		temp_elevator.set_elevator_out_of_order(false);

	} else{
		temp_elevator.set_elevator_out_of_order(true);
	}
	order_matrix_string = result[4];
	std::vector<std::vector <Queue_element> > order_matrix_temp = string_to_order_matrix(order_matrix_string);
	temp_elevator.set_elevator_order_matrix(&order_matrix_temp);
	return temp_elevator;
}

std::string Network::elevator_object_to_messagestring(Elevator &elevator){
	std::stringstream ss;
	Status elev_status = elevator.get_elevator_status();
	std::string order_matrix_string = order_matrix_to_string(elevator.get_order_matrix_ptr());
	ss << elev_status.elevator_ID << ":" << elev_status.dir << ":" << elev_status.floor << ":" << elev_status.out_of_order << ":" << order_matrix_string;
	return ss.str();
}

//----------------------------------------------------------------------------------------------------
//Public functions
//----------------------------------------------------------------------------------------------------
void Network::message_recieve(std::string message_ID, int elevator_ID){
	switch(message_id){
		case 0:		//"supervisor_informed"


			break;
		case 1:   //"new_order_matrix_for_all":

			//kjør fsm_new_master_command(new_order_matrix) på ein eller anna måte, returnere verdi til eventmanager?;

			break;
		case "slave_order_complete":
			sv_manage_completed_order(elevators[elevator_number]);
			break;
		case "slave_order_incomplete":
			sv_manage_incompleted_order(elevators[elevator_number]);
			break;
		case "slave_request_order_matrix":
			nw_distribute_order_matrix(Queue_element &order_matrix);
			break;
		default:
			break

	}

}

void Network::inform_supervisor(Elevator &elevator){

}

void Network::slave_request_order_matrix(){

}


void Network::distribute_order_matrix(std::vector<std::vector<Queue_element> > *order_matrix_ptr){


}

void Network::slave_order_complete(Elevator &elevator){


}

void Network::slave_order_incomplete(Elevator &elevator){

}

bool Network::ping_elevator(Elevator &elevator){
	bool is_elevator_responding;



	return is_elevator_responding;
}