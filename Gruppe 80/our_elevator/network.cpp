#include "network.h"

int main(){
	Network network1(3);
	string message = "1"

	return 0;
}

Network::Network(){
	n_elevators = -1;
	elevators = NULL;
	elevators_online = NULL;
}

Network::Network(int n_elevators){
	Elevator elev_temp;
	for(int i = 0; i < this->n_elevators ; i++){
		elevators[i] = elev_temp;
	}
}

//--------------------------------------------------------------------------------------------------
//Private functions
//----------------------------------------------------------------------------------------------------

void Network::nw_messagestring_to_elevator_object(std::string &message){
	messagestring_to_elevator_object(std::string messagestring){
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
	if(result[3] == "false"){
		temp_elevator.set_elevator_out_of_order(false);

	} else{
		temp_elevator.set_elevator_out_of_order(true);
	}
	order_matrix_string = result[4];
	std::vector<std::vector <Queue_element> > order_matrix_temp = string_to_order_matrix(order_matrix_string);
	temp_elevator.set_elevator_order_matrix(&order_matrix_temp);
	return temp_elevator;
}

std::string Network::nw_elevator_object_to_messagestring(Elevator &elevator){

}


//----------------------------------------------------------------------------------------------------
//Public functions
//----------------------------------------------------------------------------------------------------
void Network::nw_message_recieve(string message_id, int elevator_number){
	switch(message_id){
		case "supervisor_informed":


			break;
		case "new_order_matrix_for_all":

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

void Network::nw_inform_supervisor(Elevator &elevator){

}

void Network::nw_slave_request_order_matrix(){

}

void Network::nw_distribute_order_matrix(Queue_element &order_matrix_ptr){


}

void Network::nw_slave_order_complete(Elevator &elevator){


}

void Network::nw_slave_order_incomplete(Elevator &elevator){

}

bool Network::nw_ping_elevator(Elevator &elevator){
	bool is_elevator_responding;



	return is_elevator_responding;
}