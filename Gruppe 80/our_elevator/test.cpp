#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <istream>
#include <stdlib.h>
#include "elevator.h"
#include "const_struct_def.h"

Elevator messagestring_to_elevator_object(std::string messagestring){
	int elevator_ID;
	int floorr;
	bool out_of_order;
	Dirn dir;
	std::vector<std::string> result;
	std::string order_matrix_string;
	std::stringstream ss1(text);

	std::string line;
	while(std::getline(ss1,line, ':')){
		result.push_back(line);
	}
	elevator_ID = atoi(result[0].c_str());
	switch(atoi(result[1].c_str())){
		case 0:
			dir = D_Stop;
			break;
		case 1:
			dir = D_Up;
			break;
		case -1:
			dir = D_Down;
			break;
	}
	floorr = atoi(result[2].c_str());
	if(result[3] == "false"){
		out_of_order = false;

	} else{
		out_of_order = true;
	}
	order_matrix_string = result[4];
	std::stringstream ss2(order_matrix_string);
	int count = 0;
	int temp_floor = 0;
	Queue_element temp;
	std::string act_btn;
	std::string elv_id;
	while(std::getline(ss2,line, '&')){
		if(count == 3){
			temp_floor +=1;
			count = 0;
		}

		if(line.size() == 2){
			act_btn = line[0];
			elv_id = line[1];
		} else if(line.size() == 3){
			act_btn = line[0];
			elv_id = line.substr(1, 2);
		}
		
		temp.active_button = atoi(act_btn.c_str());
		temp.elevator_ID = atoi(elv_id.c_str());
		order_matrix[temp_floor][count] = temp;
		count += 1;
	}


	std::cout << "elev id: " << elevator_ID << " dir: " << dir << " floor: " << floorr << " out_of_order: " \
	<< out_of_order << " order_matrix_string: " << order_matrix_string << std::endl;

	std::cout << "Order matrix: " << std::endl;
	for(int i = 0; i < n_floors;i++){
		for(int j = 0; j < n_buttons; j++){
			std::cout << order_matrix[i][j].active_button << ":" << order_matrix[i][j].elevator_ID << ";";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return temp_elev;
}

int main(){
	
	int n_floors = 4;
	int n_buttons = 3;
	Queue_element** order_matrix;
	order_matrix = new Queue_element*[n_floors];
	for(int i=0;i<n_floors;i++){
		order_matrix[i] = new Queue_element [n_buttons];//{};
	}
	for(int i=0;i<n_floors;i++){
		for(int j=0;j<n_buttons;j++){
			order_matrix[i][j].active_button = 0;
			order_matrix[i][j].elevator_ID = -1;
		}
	}

	std::string text = "1:1:3:false:01&13&01&0-1&11&1-1&0-1&14&01&1-1&13&00&";
	Elevator temp;
	temp = messagestring_to_elevator_object(text);

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