#include "network.h"


Network::Network(){
	Elevator* elev_temp = new Elevator;
	std::vector<std::vector<Queue_element> > temp = twoD_vector_init();
	elev_temp->set_elevator_order_matrix(&temp);
	for(unsigned int i = 0; i < N_ELEVATORS ; i++){
		this->elevators.push_back(elev_temp);
		elevators[i]->set_elevator_ID(i);
	}
	this->master_ip = "0";
}

Network::Network(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix_ptr, int elevator_ID){
	
	Elevator* elev_temp_this = new Elevator(elevator_status, order_matrix_ptr);
	Elevator* elev_temp_others = new Elevator(elevator_status);
	if(elevator_status.role == MASTER){	
		this->master_ip = elevator_status.ip;
	}
	else{
		this->master_ip = "0";
	}
	
	for(unsigned int i = 0; i < N_ELEVATORS ; i++){
		if(i != elevator_ID){
			this->elevators.push_back(elev_temp_others);
			elevators[i]->set_elevator_ID(i);
		} else{
			this->elevators.push_back(elev_temp_this);
		}
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
	switch(atoi(result[6].c_str())){
		case 0:
			temp_elevator.set_elevator_current_state(MOVING);
			break;
		case 1:
			temp_elevator.set_elevator_current_state(IDLE);
			break;
		case 2:
			temp_elevator.set_elevator_current_state(DOOR_OPEN);
			break;
	}
	order_matrix_string = result[7];
	std::vector<std::vector <Queue_element> > order_matrix_temp = string_to_order_matrix(order_matrix_string);
	temp_elevator.set_elevator_order_matrix(&order_matrix_temp);
	
	return temp_elevator;
}

std::string Network::elevator_object_to_messagestring(Elevator &elevator){
	std::stringstream ss;
	Status elev_status = elevator.get_elevator_status();
	std::string order_matrix_string = order_matrix_to_string(elevator.get_order_matrix_ptr());
	ss << elev_status.ip << ":" << elev_status.role << ":" << elev_status.elevator_ID << ":" << elev_status.dir << ":" << elev_status.floor << ":" << elev_status.out_of_order << ":" << elev_status.current_state << ":" << order_matrix_string;
	return ss.str();
}

//----------------------------------------------------------------------------------------------------
//Public functions
//----------------------------------------------------------------------------------------------------




void Network::handle_message(Message message, int foreign_elevator_ID, int this_elevator_ID){
	switch(message){
		case MASTER_IP_INIT:
			this->master_ip = elevators[foreign_elevator_ID]->get_elevator_ip();
			break;
		case HANDSHAKE:
			send_message_packet(HANDSHAKE, this_elevator_ID);
			}
		case SLAVE_REQUEST_ORDER_MATRIX:
			std::cout << "I recieved your message: SLAVE_REQUEST_ORDER_MATRIX, here is the elevator you sent me: " << std::endl;
			elevators[foreign_elevator_ID]->print_elevator();
			std::cout << "Distributing order matrix:" << std::endl;
			std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
			sv_manage_order_matrix(elevators);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID);
			break;
		case SLAVE_ORDER_COMPLETE:
			sv_manage_completed_order(elevators[this_elevator_ID]);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID);
			break;
		case SLAVE_ORDER_INCOMPLETE:
			//sv_manage_incomplete_order(elevators[elevator_ID]);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID);
			break;
		case SLAVE_SEND_ELEVATOR_INFORMATION:
			std::cout << "I recieved your message: SLAVE_SEND_ELEVATOR_INFORMATION" << std::endl;
			std::cout << ", here is the elevator you sent me: " << std::endl;
			elevators[foreign_elevator_ID]->print_elevator();
			std::cout << "---------------------------------------------------" << std::endl;
			sv_manage_order_matrix(elevators);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID);
			break;
		case MASTER_DISTRIBUTE_ORDER_MATRIX: //Slave receives
			std::cout << "I recieved your message: MASTER_DISTRIBUTE_ORDER_MATRIX, thank you for the \
			new elevator" << std::endl;
			this->master_ip = elevators[foreign_elevator_ID]->get_elevator_ip();
			break;
		default:
			std::cout << "Invalid message, but i will accept your elevator" << std::endl;
			break;
	}
}


void Network::recieve_message_packet(int this_elevator_ID){
	Message message;
	std::string datastring;
	std::string messagestring;
	struct code_message packet;
	switch(elevators[this_elevator_ID]->get_elevator_role()){
		case MASTER:
			packet = udp_reciever();
			break;
		case SLAVE:
			packet = udp_recieve_broadcast();
			break;
	}
	datastring.assign(packet.data);
	message = message_id_string_to_enum(datastring.substr(0,1));
	messagestring = datastring.substr(datastring.find_first_of(":")+1,datastring.npos);

	Elevator temp_elevator = messagestring_to_elevator_object(messagestring);
	Status temp_status = temp_elevator.get_elevator_status();
	elevators[temp_status.elevator_ID]->set_elevator_status(temp_status);
	elevators[temp_status.elevator_ID]->set_elevator_order_matrix(temp_elevator.get_order_matrix_ptr());
	handle_message(message, temp_status.elevator_ID, this_elevator_ID);

}

void Network::send_message_packet(Message message, int elevator_ID, std::string foreign_elevator_ip){
	std::string message_string;
	char * ip = new char[master_ip.size() + 1];
	std::copy(master_ip.begin(), master_ip.end(), ip);
	ip[master_ip.size()] = '\0'; // don't forget the terminating 0
	switch(message){
		case MASTER_IP_INIT:
			message_string = "0:";
			udp_broadcaster(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]));
			break;
		case HANDSHAKE:
			message_string = "1:";
			//udp_sender()
			udp_broadcaster(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]));
			break;
		case SLAVE_REQUEST_ORDER_MATRIX:
			message_string = "1:";
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]), MASTERPORT, ip);
			break;
		case SLAVE_ORDER_COMPLETE:
			message_string = "2:";
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]), MASTERPORT, ip);
			break;
		case SLAVE_ORDER_INCOMPLETE:
			message_string = "3:",
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]),MASTERPORT, ip);
			break;
		case SLAVE_SEND_ELEVATOR_INFORMATION:
			message_string = "4:";
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]), MASTERPORT, ip);
			break;
		case MASTER_DISTRIBUTE_ORDER_MATRIX:
			message_string = "5:"; 
			udp_broadcaster(message_string + elevator_object_to_messagestring(*elevators[elevator_ID]));
			break;	
		default:
			std::cout << "Not a valid message" << std::endl;
	}
	delete[] ip;
}


bool Network::is_node_responding(int this_elevator_ID, int foreign_elevator_ID){
	struct code_message code;
	switch(my_elevator->get_elevator_role()){
			case MASTER:
				send_message_packet(HANDSHAKE, this_elevator_ID, elevators[foreign_elevator_ID]->get_elevator_ip()); 
				break;
			case SLAVE:
				send_message_packet(HANDSHAKE, this_elevator_ID, "")
				break;
		}
	
	code = udp_reciever();
	return code.responding;
}

void listen_on_network(Elevator* my_elevator, Network &my_network, Queue &my_queue){
	while(1){
		switch(my_elevator->get_elevator_role()){
			case MASTER:
				//usleep(250000);
				my_network.is_node_responding(my_elevator->get_elevator_ID(), );
				my_network.recieve_message_packet(my_elevator->get_elevator_ID());

				break;
			case SLAVE:
				//usleep(250000);
				if(!my_network.is_node_responding(my_elevator->get_elevator_ID())){

				}
				
				my_network.recieve_message_packet(my_elevator->get_elevator_ID());
				break;
		}
	}
}