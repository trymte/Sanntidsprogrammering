#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "elevator.h"


Elevator test_messagestring_to_elevator_object(std::string &messagestring){
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


std::string elevator_object_to_messagestring(Elevator &elevator){
	std::stringstream ss;
	Status elev_status = elevator.get_elevator_status();
	std::string order_matrix_string = order_matrix_to_string(elevator.get_order_matrix_ptr());
	ss << elev_status.ip << ":" << elev_status.role << ":" << elev_status.elevator_ID << ":" << elev_status.dir << ":" << elev_status.floor << ":" \
	<< elev_status.out_of_order << ":" << elev_status.current_state << ":" << order_matrix_string;
	return ss.str();
}

int main(){
	
	

	std::string text = "129.241.187.161:1:1:1:3:0:1:01&13&01&0-1&11&1-1&0-1&14&01&1-1&13&00&";
	Elevator temp = test_messagestring_to_elevator_object(text);
	
	//print_order_matrix(temp.get_order_matrix_ptr());
	//std::string messagestring = elevator_object_to_messagestring(temp);
	//std::cout << messagestring << std::endl;
	temp.print_elevator();
	return 0;
}