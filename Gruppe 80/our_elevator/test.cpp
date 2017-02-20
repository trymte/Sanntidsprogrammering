#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "elevator.h"

void print_order_matrix(std::vector<std::vector <Queue_element> > order_matrix){
	std::cout << "Order matrix: " << std::endl;
	for(int i = 0; i < N_FLOORS;i++){
		for(int j = 0; j < N_BUTTONS; j++){
			std::cout << order_matrix[i][j].active_button << ":" << order_matrix[i][j].elevator_ID << ";";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::vector<std::vector <Queue_element> > string_to_order_matrix(std::string order_matrix_string){

	Queue_element** order_matrix = 0;
	order_matrix = new Queue_element*[N_FLOORS];
	for(int i=0;i<N_FLOORS;i++){
		order_matrix[i] = new Queue_element[N_BUTTONS];//{};
	}
	for(int i=0;i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			order_matrix[i][j].active_button = 0;
			order_matrix[i][j].elevator_ID = -1;
		}
	}
	std::stringstream ss2(order_matrix_string);
	int count = 0;
	int temp_floor = 0;
	Queue_element temp_queue_element;
	std::string queue_element_string;
	std::string act_btn;
	std::string elv_id;
	while(std::getline(ss2,queue_element_string, '&')){
		if(count == 3){
			temp_floor +=1;
			count = 0;
		}
		if(queue_element_string.size() == 2){
			act_btn = queue_element_string[0];
			elv_id = queue_element_string[1];
		} else if(queue_element_string.size() == 3){
			act_btn = queue_element_string[0];
			elv_id = queue_element_string.substr(1, 2);
		}
		if(act_btn == "0"){
			temp_queue_element.active_button = false;
		} else{
			temp_queue_element.active_button = true;
		}
		
		temp_queue_element.elevator_ID = atoi(elv_id.c_str());
		order_matrix[temp_floor][count] = temp_queue_element;
		count += 1;
	}
	print_order_matrix(order_matrix);
	std::cout << order_matrix << std::endl;
	return order_matrix;
}

Elevator messagestring_to_elevator_object(std::string messagestring){
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
	std::cout << "hello" << std::endl;
	Queue_element** order_matrix = string_to_order_matrix(order_matrix_string); //segfault here
	temp_elevator.set_elevator_order_matrix_ptr(&order_matrix);
	std::cout << "hello2" << std::endl;
	
	Status elev_status = temp_elevator.get_elevator_status();
	std::cout << "elev id: " << elev_status.elevator_ID << " dir: " << elev_status.dir << " floor: " << elev_status.floor << " out_of_order: " \
	<< elev_status.out_of_order << " order_matrix_string: " << order_matrix_string << std::endl;
	return temp_elevator;
}




int main(){
	
	

	std::string text = "1:1:3:false:01&13&01&0-1&11&1-1&0-1&14&01&1-1&13&00&";
	Elevator temp = messagestring_to_elevator_object(text);
	print_order_matrix(temp.get_order_matrix_ptr());
	return 0;
}








//typedef vector<vector <Queue_element> > 2d_array;
/*Queue_element initial;
	initial.active_button = 0;
	initial.elevator_ID = 1;
	2d_array matrix;
	2d_array *matrix_ptr;

	matrix.resize(4, vector<Queue_element>(3, initial));

	for(auto outer = matrix.begin(); outer != matrix.end(); outer++){
		for(auto inner = outer->begin(); inner != outer->begin(); inner++){
			cout << inner->active_button << ": " << inner->elevator_ID << ";";
		}
		cout << endl;
	}
	*/