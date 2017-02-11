

Network::Network(int n_elevators){
	this->n_elevators = n_elevators;
	Status temp = {0,0,"",false};
	Elevator elev_temp(temp);
	for(int i = 0; i < this->n_elevators ; i++){
		elevators[i] = elev_temp;
	}
}

void Network::nw_message_recieve(string message_id, int elevator_number){
	switch(message_id){
		case "supervisor_informed":


			break;
		case "new_order_matrix":


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