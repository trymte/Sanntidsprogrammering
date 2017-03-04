#include "network.h"


Network::Network(){
	

	Elevator elev_temp;
//	elev_temp.set_elevator_status(init_status);

//Ikke god løsning, se på det senere
	//Queue q_temp;
	//elev_temp.set_elevator_order_matrix(q_temp.get_order_matrix_ptr());
//


	for(unsigned int i = 0; i < N_ELEVATORS ; i++){
		this->elevators.push_back(elev_temp);
		elevators[i].set_elevator_ID(i);
	}

}

Network::Network(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix_ptr){
	Elevator elev_temp(elevator_status, order_matrix_ptr);
	for(unsigned int i = 0; i < N_ELEVATORS ; i++){
		this->elevators.push_back(elev_temp);
		elevators[i].set_elevator_ID(i);
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
	temp_elevator.set_elevator_ip(result[0]);
	switch(atoi(result[1].c_str())){
		case 0:
			temp_elevator.set_elevator_role(SLAVE);
		break;
		case 1:
			temp_elevator.set_elevator_role(MASTER);
		break;
	}
	temp_elevator.set_elevator_ID(atoi(result[2].c_str()));
	switch(atoi(result[3].c_str())){
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
	temp_elevator.set_elevator_floor(atoi(result[4].c_str()));
	if(result[5] == "0"){
		temp_elevator.set_elevator_out_of_order(false);

	} else{
		temp_elevator.set_elevator_out_of_order(true);
	}
	order_matrix_string = result[6];
	std::vector<std::vector <Queue_element> > order_matrix_temp = string_to_order_matrix(order_matrix_string);
	temp_elevator.set_elevator_order_matrix(&order_matrix_temp);
	Status elev_status = temp_elevator.get_elevator_status();
	
	return temp_elevator;
}

std::string Network::elevator_object_to_messagestring(Elevator &elevator){
	std::stringstream ss;
	Status elev_status = elevator.get_elevator_status();
	std::string order_matrix_string = order_matrix_to_string(elevator.get_order_matrix_ptr());
	ss << elev_status.ip << ":" << elev_status.role << ":" << elev_status.elevator_ID << ":" << elev_status.dir << ":" << elev_status.floor << ":" << elev_status.out_of_order << ":" << order_matrix_string;
	return ss.str();
}

//----------------------------------------------------------------------------------------------------
//Public functions
//----------------------------------------------------------------------------------------------------






void Network::handle_message(Message message, int elevator_ID){
	switch(message){
		case SLAVE_REQUEST_ORDER_MATRIX:
			std::cout << "I recieved your message: SLAVE_REQUEST_ORDER_MATRIX, here is the elevator you sent me: " << std::endl;
			elevators[elevator_ID].print_elevator();
			break;
		case SLAVE_ORDER_COMPLETE:
			//sv_manage_completed_order(elevators[elevator_ID]);
			break;
		case SLAVE_ORDER_INCOMPLETE:
			//sv_manage_incomplete_order(elevators[elevator_ID]);
			break;
		case SLAVE_SEND_ELEVATOR_INFORMATION:
			//sv_manage_order_matrix(elevators);
			break;
		case MASTER_DISTRIBUTE_ORDER_MATRIX:
			std::cout << "I recieved your message: MASTER_DISTRIBUTE_ORDER_MATRIX, master" << std::endl;
			for(unsigned int i = 0; i < N_ELEVATORS; i ++){
				elevators[i].set_elevator_order_matrix(elevators[elevator_ID].get_order_matrix_ptr());
			}
			break;
	}

}


void Network::slave_recieve_message_packet(){
	Message message;
	std::string datastring;
	std::string messagestring;
	struct code_message packet = udp_recieve_broadcast();
	datastring.assign(packet.data);
	message = message_id_string_to_enum(datastring.substr(0,1));
	messagestring = datastring.substr(datastring.find_first_of(":")+1,datastring.npos);

	Elevator temp_elevator = messagestring_to_elevator_object(messagestring);
	Status temp_status = temp_elevator.get_elevator_status();
	elevators[temp_status.elevator_ID].set_elevator_order_matrix(temp_elevator.get_order_matrix_ptr());
	handle_message(message, temp_status.elevator_ID);
}

void Network::master_recieve_message_packet(){
	Message message;
	std::string datastring;
	std::string messagestring;
	struct code_message packet = udp_reciever();
	datastring.assign(packet.data);
	message = message_id_string_to_enum(datastring.substr(0,1));
	messagestring = datastring.substr(datastring.find_first_of(":")+1,datastring.npos);

	Elevator temp_elevator = messagestring_to_elevator_object(messagestring);
	Status temp_status = temp_elevator.get_elevator_status();
	elevators[temp_status.elevator_ID].set_elevator_order_matrix(temp_elevator.get_order_matrix_ptr());
	handle_message(message, temp_status.elevator_ID);

}

void Network::send_message_packet(Message message, int elevator_ID){
	std::string message_string;
	char * ip = new char[message_string.size() + 1];
	std::copy(message_string.begin(), message_string.end(), ip);
	ip[message_string.size()] = '\0'; // don't forget the terminating 0
	switch(message){
		case SLAVE_REQUEST_ORDER_MATRIX:
			message_string = "0:";
			udp_sender(message_string + elevator_object_to_messagestring(elevators[elevator_ID]),MASTERPORT, ip);
			break;
		case SLAVE_ORDER_COMPLETE:
			message_string = "1:";
			udp_sender(message_string + elevator_object_to_messagestring(elevators[elevator_ID]), MASTERPORT, ip);
			break;
		case SLAVE_ORDER_INCOMPLETE:
			message_string = "2:",
			udp_sender(message_string + elevator_object_to_messagestring(elevators[elevator_ID]),MASTERPORT, ip);
			break;
		case SLAVE_SEND_ELEVATOR_INFORMATION:
			message_string = "3:";
			udp_broadcaster(message_string + elevator_object_to_messagestring(elevators[elevator_ID]));
			break;
		case MASTER_DISTRIBUTE_ORDER_MATRIX:
			message_string = "4:"; 
			udp_broadcaster(message_string + elevator_object_to_messagestring(elevators[elevator_ID]));
			break;	
		default:
			std::cout << "No valid message" << std::endl;
	}
	delete[] ip;
}