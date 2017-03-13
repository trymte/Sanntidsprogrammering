#include "network.h"


Network::Network(){
	
	Elevator* elev_temp = new Elevator;
	std::vector<std::vector<Queue_element> > temp = init_twoD_vector();
	elev_temp->set_order_matrix(&temp);
	for(unsigned int i = 0; i < N_ELEVATORS ; i++){
		this->elevators.push_back(elev_temp);
		elevators[i]->set_ID(i);
	}
	this->master_ip = "0";
	this->master_ID = 0;	
}

Network::Network(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix_ptr, int elevator_ID){
	this->master_ID = 0;	
	Elevator* elev_temp_this = new Elevator(elevator_status, order_matrix_ptr);
	elev_temp_this->set_online(true);
	if(elevator_status.role == MASTER){	
		this->master_ip = elevator_status.ip;
	}
	else{
		this->master_ip = "0";
	}
	
	for(unsigned int i = 0; i < N_ELEVATORS ; i++){
		Elevator* elev_temp_others = new Elevator(elevator_status);
		elev_temp_others->set_ip("0");
		elev_temp_others->set_role(SLAVE);
		if(i != elevator_ID){
			this->elevators.push_back(elev_temp_others);
		} else{
			this->elevators.push_back(elev_temp_this);
		}
		elevators[i]->set_ID(i);
	}

}

Network::~Network(){
	if (elevators.size() != 0){
		for(unsigned int i = 0; i < N_ELEVATORS; i++){
			delete elevators[i];
		}
		this->elevators.erase(this->elevators.begin(),this->elevators.end());
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
	temp_elevator.set_ip(result[0]);
	temp_elevator.set_role((Role)atoi(result[1].c_str()));
	temp_elevator.set_ID(atoi(result[2].c_str()));
	temp_elevator.set_dir((Dirn)atoi(result[3].c_str()));
	temp_elevator.set_floor(atoi(result[4].c_str()));
	temp_elevator.set_last_floor(atoi(result[5].c_str()));
	temp_elevator.set_out_of_order((bool)result[6].compare("0"));
	temp_elevator.set_online((bool)result[7].compare("0")); 
	temp_elevator.set_current_state((State)atoi(result[8].c_str()));
	order_matrix_string = result[9];
	std::vector<std::vector <Queue_element> > order_matrix_temp = string_to_order_matrix(order_matrix_string);
	temp_elevator.set_order_matrix(&order_matrix_temp);


	return temp_elevator;
}

std::string Network::elevator_object_to_messagestring(Elevator &elevator){
	std::stringstream ss;
	Status elev_status = elevator.get_status();
	std::string order_matrix_string = order_matrix_to_string(elevator.get_order_matrix_ptr());
	ss << elev_status.ip << ":" << elev_status.role << ":" << elev_status.elevator_ID << ":" << elev_status.dir << ":" << elev_status.floor << ":" << 
		elev_status.last_floor << ":" << elev_status.out_of_order  << ":" << elev_status.online << ":" << elev_status.current_state << ":" << order_matrix_string;
	return ss.str();
}

//----------------------------------------------------------------------------------------------------
//Public functions
//----------------------------------------------------------------------------------------------------

void Network::handle_message(Message message, int this_elevator_ID, int foreign_elevator_ID){
	switch(message){
		case MASTER_IP_INIT:
			this->master_ip = elevators[foreign_elevator_ID]->get_status().ip;
			break;

		case SLAVE_IP_INIT:
			// Master sets IP of slave in recieve_message_packet
			break;

		case HANDSHAKE:
			send_message_packet(HANDSHAKE, this_elevator_ID, elevators[foreign_elevator_ID]->get_status().ip);
			break;

		case SLAVE_ORDER_COMPLETE:
			sv_manage_completed_order(elevators[foreign_elevator_ID]);
			sv_manage_order_matrix(elevators, foreign_elevator_ID);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID, "");
			break;

		case SLAVE_ORDER_INCOMPLETE:
			sv_manage_completed_order(elevators[foreign_elevator_ID]);
			sv_manage_order_matrix(elevators, foreign_elevator_ID);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID, "");
			break;

		case SLAVE_SEND_ELEVATOR_INFORMATION:
			sv_manage_order_matrix(elevators, foreign_elevator_ID);
			send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, this_elevator_ID, "");
			break;

		case MASTER_DISTRIBUTE_ORDER_MATRIX: 
			for(unsigned int i= 0; i < N_ELEVATORS; i++){
				elevators[i]->set_order_matrix(elevators[foreign_elevator_ID]->get_order_matrix_ptr());
			}
			break;
	}
}

void Network::recieve_message_packet(int this_elevator_ID){
	std::string datastring;
	std::string messagestring;
	struct code_message packet;
	switch(elevators[this_elevator_ID]->get_status().role){
		case MASTER:
			packet = udp_reciever();
			break;
		case SLAVE:
			packet = udp_recieve_broadcast();
			break;
	}
	datastring.assign(packet.data);
	if((datastring.length() > MIN_MESSAGE_LENGTH) && (datastring[1] == ':')){
		Message message = (Message)atoi(datastring.substr(0,1).c_str());
		messagestring = datastring.substr(datastring.find_first_of(":")+1,datastring.npos);
		Elevator temp_elevator = messagestring_to_elevator_object(messagestring);

		if(temp_elevator.get_status().ip != elevators[this_elevator_ID]->get_status().ip){
			Status temp_status = temp_elevator.get_status();
			temp_status.role = elevators[temp_status.elevator_ID]->get_status().role;
			temp_status.online = elevators[temp_status.elevator_ID]->get_status().online;
			elevators[temp_status.elevator_ID]->set_status(temp_status);
			elevators[temp_status.elevator_ID]->set_order_matrix(temp_elevator.get_order_matrix_ptr());
			handle_message(message, this_elevator_ID, temp_status.elevator_ID);
		}
	}
}

void Network::recieve_handshake_message(int this_elevator_ID){
	std::string datastring;
	std::string messagestring;
	struct code_message packet;
	packet = udp_handshake_reciever();
	datastring.assign(packet.data);
	if((datastring.length() !=0) && (datastring[1] == ':')){
		Message message = (Message)atoi(datastring.substr(0,1).c_str());
		messagestring = datastring.substr(datastring.find_first_of(":")+1,datastring.npos);
		Elevator temp_elevator = messagestring_to_elevator_object(messagestring);
		Status temp_status = temp_elevator.get_status();
		handle_message(message, this_elevator_ID, temp_status.elevator_ID);
	}	
}

void Network::send_message_packet(Message message, int this_elevator_ID, std::string reciever_ip){
	std::string message_string;
	char * ip = new char[reciever_ip.size() + 1];
	std::copy(reciever_ip.begin(), reciever_ip.end(), ip);
	ip[reciever_ip.size()] = '\0'; 
	switch(message){
		case MASTER_IP_INIT:
			message_string = "0:";
			udp_broadcaster(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]));
			break;

		case SLAVE_IP_INIT:
			message_string = "1:";
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]), MASTERPORT, ip);
			break;

		case HANDSHAKE:
			message_string = "2:";
			udp_handshake_sender(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]), PINGPORT, ip);
			break;

		case SLAVE_ORDER_COMPLETE:
			message_string = "3:";
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]), MASTERPORT, ip);
			break;

		case SLAVE_ORDER_INCOMPLETE:
			message_string = "4:",
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]),MASTERPORT, ip);
			break;

		case SLAVE_SEND_ELEVATOR_INFORMATION:
			message_string = "5:";
			udp_sender(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]), MASTERPORT, ip);
			break;

		case MASTER_DISTRIBUTE_ORDER_MATRIX:
			message_string = "6:"; 
			udp_broadcaster(message_string + elevator_object_to_messagestring(*elevators[this_elevator_ID]));
			break;	
	}		
	delete[] ip;
}

bool Network::is_node_responding(int this_elevator_ID, int foreign_elevator_ID){
	if ((elevators[foreign_elevator_ID]->get_status().ip == "0") || (elevators[this_elevator_ID]->get_status().ip == elevators[foreign_elevator_ID]->get_status().ip)){
		return false;
	}
	struct code_message code;
	send_message_packet(HANDSHAKE, this_elevator_ID, this->elevators[foreign_elevator_ID]->get_status().ip);
	code = udp_handshake_reciever();
	return code.responding;
}

void Network::check_responding_elevators(int this_elevator_ID){
	for(unsigned int i = 0; i < N_ELEVATORS; i++){
		if ((elevators[this_elevator_ID]->get_status().role == MASTER) && (elevators[i]->get_status().online == false)){
			
			handle_message(SLAVE_ORDER_INCOMPLETE,this_elevator_ID,i);
		}

		std::cout << "elev " << i << "\tonline: " << this->elevators[i]->get_status().online << "\tip: " << this->elevators[i]->get_status().ip << std::endl;
		if(i != this_elevator_ID){
			int ping_count = 0;
			for (unsigned int j = 0; j<NUMBER_OF_PINGS; j++){
				ping_count += is_node_responding(this_elevator_ID, i);
			}

			if(ping_count != 0){
				elevators[i]->set_online(true);
			}
			else{
				elevators[i]->set_online(false);
			}
		}	
	}
}

void Network::check_my_role(int this_elevator_ID){
	for(unsigned int i = 0; i < N_ELEVATORS; i++){
		if(this->elevators[i]->get_status().online){
			master_ID = this->elevators[i]->get_status().elevator_ID;
			break;
		}
		
	}
	if((master_ID == this_elevator_ID) && (this->elevators[this_elevator_ID]->get_status().role == SLAVE)){
		this->elevators[this_elevator_ID]->set_role(MASTER);
		std::cout << "Role changed from slave to master: " << std::endl;
	}
	else if ((master_ID != this_elevator_ID) && (this->elevators[this_elevator_ID]->get_status().role == MASTER)){
		this->elevators[this_elevator_ID]->set_role(SLAVE);
		std::cout << "Role changed from master to slave: " <<  std::endl;
	}
	this->master_ip = this->elevators[master_ID]->get_status().ip;
} 

// End of class


// ------------------------------------------------------------------------------------------------
//         Network threads for send, ping and recieving messages
// ------------------------------------------------------------------------------------------------

void network_send(Elevator* my_elevator, Network &my_network){
	while(1){
		usleep(100000);
		switch(my_elevator->get_status().role){
			case MASTER:
				my_network.send_message_packet(MASTER_IP_INIT, my_elevator->get_status().elevator_ID,"");
				break;
			case SLAVE:
				my_network.send_message_packet(SLAVE_IP_INIT, my_elevator->get_status().elevator_ID, my_network.get_master_ip());
				break;
		}
	}
}

void network_recieve(Elevator* my_elevator, Network &my_network){
	std::mutex my_mutex1;
	while(1){
		usleep(25000);
		my_mutex1.lock();
		
		my_network.recieve_message_packet(my_elevator->get_status().elevator_ID);
		
		my_mutex1.unlock();
	}
}

void network_ping(Elevator* my_elevator, Network &my_network){
	std::mutex my_mutex2;
	while(1){
		usleep(1000000);
		my_mutex2.lock();
		my_network.check_my_role(my_elevator->get_status().elevator_ID);
		my_mutex2.unlock();
		my_network.check_responding_elevators(my_elevator->get_status().elevator_ID);
		my_network.recieve_handshake_message(my_elevator->get_status().elevator_ID);
	}
}