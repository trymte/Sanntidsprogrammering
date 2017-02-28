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
	switch(atoi(result[0].c_str())){
		case 0:
			temp_elevator.set_elevator_role(SLAVE);
		break;
		case 1:
			temp_elevator.set_elevator_role(MASTER);
		break;
	}
	temp_elevator.set_elevator_ID(atoi(result[1].c_str()));
	switch(atoi(result[2].c_str())){
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
	temp_elevator.set_elevator_floor(atoi(result[3].c_str()));
	if(result[4] == "0"){
		temp_elevator.set_elevator_out_of_order(false);

	} else{
		temp_elevator.set_elevator_out_of_order(true);
	}
	order_matrix_string = result[5];
	std::vector<std::vector <Queue_element> > order_matrix_temp = string_to_order_matrix(order_matrix_string);
	temp_elevator.set_elevator_order_matrix(&order_matrix_temp);
	return temp_elevator;
}

std::string Network::elevator_object_to_messagestring(Elevator &elevator){
	std::stringstream ss;
	Status elev_status = elevator.get_elevator_status();
	std::string order_matrix_string = order_matrix_to_string(elevator.get_order_matrix_ptr());
	ss << elev_status.role << ":" << elev_status.elevator_ID << ":" << elev_status.dir << ":" << elev_status.floor << ":" << elev_status.out_of_order << ":" << order_matrix_string;
	return ss.str();
}

//----------------------------------------------------------------------------------------------------
//Public functions
//----------------------------------------------------------------------------------------------------
void Network::handle_message(Message message, int elevator_ID){
	switch(message){
		case SLAVE_REQUEST_ORDER_MATRIX:
			//distribute_orderMatrix
		break;
		case SLAVE_ORDER_INCOMPLETE:
			//set out_of order til 0
		break;
		case SLAVE_SEND_ELEVATOR_INFORMATION:
			//update_order_matrix and distribute
		break;
		case MASTER_DISTRIBUTE_ORDER_MATRIX:
			//distribute_order_matrix
		break;
	}

}


//Trenger egentlig ikkje desse funksjonane, kan berre skrive send_message_packet(SLAVE_REQUEST_ORDER_MATRIX, elev.get_elevator_status().elevator_ID);
void Network::slave_send_elevator_information(int elevator_ID){
	Message message = SLAVE_SEND_ELEVATOR_INFORMATION;
	send_message_packet(message, elevator_ID);
}

void Network::slave_request_order_matrix(int elevator_ID){
	Message message = SLAVE_REQUEST_ORDER_MATRIX;
	send_message_packet(message, )
}


void Network::distribute_order_matrix(int elevator_ID){
	Message message = MASTER_DISTRIBUTE_ORDER_MATRIX;
	send_message_packet(message, elevator_ID);
}


void Network::slave_order_incomplete(int elevator_ID){
	Message message = SLAVE_ORDER_INCOMPLETE;
	send_message_packet(message, elevator.get_elevator_status().elevator_ID);
}

void Network::recieve_message_packet(){
	Message message;
	std::string datastring;
	std::string messagestring;
	struct code_message packet = udp_recieve_broadcast();
	datastring.assign(packet.data);
	message = message_id_string_to_enum(datastring.substr(0,1));
	messagestring = datastring.substr(datastring.find_first_of(":")+1,datastring.npos());

	Elevator temp_elevator = messagestring_to_elevator_object(messagestring);
	Status temp_status = temp_elevator.get_elevator_status();
	elevators[temp_status.elevator_ID] = temp_elevator;
	handle_message(message, temp_status.elevator_ID);
}

void Network::send_message_packet(Message message, int elevator_ID){
	std::string message;
	switch(message){
		case SLAVE_REQUEST_ORDER_MATRIX:
			message = "0";
			udp_sender(message + elevator_object_to_messagestring(elevators[elevator_ID]),MASTERPORT, UDP_SEND_IP);
		break;
		case SLAVE_ORDER_INCOMPLETE:
			message = "1",
			udp_sender(message + elevator_object_to_messagestring(elevators[elevator_ID]),MASTERPORT, UDP_SEND_IP);
		break;
		case SLAVE_SEND_ELEVATOR_INFORMATION:
			message = "2";
			udp_broadcaster(message + elevator_object_to_messagestring(elevators[elevator_ID]));
		break;
		case MASTER_DISTRIBUTE_ORDER_MATRIX:
			message = "3"; 
			udp_broadcaster(message + elevator_object_to_messagestring(elevators[elevator_ID]));
		break;	
	}
}