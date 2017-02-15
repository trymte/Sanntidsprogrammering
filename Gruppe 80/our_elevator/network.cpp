
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
	this->n_elevators = n_elevators;
	Status temp = {0,0,"",false};
	Elevator elev_temp(temp);
	for(int i = 0; i < this->n_elevators ; i++){
		elevators[i] = elev_temp;
	}
}

//--------------------------------------------------------------------------------------------------
//Private functions
//----------------------------------------------------------------------------------------------------


void Network::nw_messagestring_to_elevator_object(string &message){
	if(message.empty()){
		std::cout << "Error empty message" << std::endl;
		return;
	}
	else{
	std::stringstream ss(message);
	Elevator elevator1;
	std::string order_matrix_string;
	ss >> elevator1.elevator_status.elevator_id >> elevator1.elevator_status.dir >> elevator1.elevator_status.floor >> elevator1.elevator_status.out_of_order >> order_matrix_string;
	


	return elevator1;
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