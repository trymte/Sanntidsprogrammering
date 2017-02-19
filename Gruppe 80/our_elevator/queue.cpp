
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "queue.h"
#include "elevator.h"
//#include "network.h"




//--------------------------------------------------------------------------------------------------
//Constructor and destructor
//----------------------------------------------------------------------------------------------------
Queue::Queue(){
	std::vector<std::vector<Queue_element> > temp;
	this->order_matrix = temp;

	for (int i=0;i<N_FLOORS;i++){
		std::vector<Queue_element> rowvector;
		for(int j=0;j<N_BUTTONS;j++){
			Queue_element init_element;
			init_element.active_button = 0;
			init_element.elevator_ID = -1;
			rowvector.push_back(init_element);
		}
		order_matrix.push_back(rowvector);
	}	
	this->order_matrix_ptr = &order_matrix;
}


Queue::Queue(unsigned int n_floors,unsigned int n_buttons){
	std::vector<std::vector<Queue_element> > temp;
	this->order_matrix = temp;

	for (int i=0;i<n_floors;i++){
		std::vector<Queue_element> rowvector;
		for(int j=0;j<n_buttons;j++){
			Queue_element init_element;
			init_element.active_button = 0;
			init_element.elevator_ID = -1;
			rowvector.push_back(init_element);
		}
		order_matrix.push_back(rowvector);
	}
	this->order_matrix_ptr = &order_matrix;
}

Queue::~Queue(){
	std::vector<std::vector<Queue_element> >::iterator row;

	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		row->erase(row->begin(),row->end());
	}
	this->order_matrix.erase(this->order_matrix.begin(),this->order_matrix.end());
}


//--------------------------------------------------------------------------------------------------
//Private member functions
//----------------------------------------------------------------------------------------------------
/*
unsigned int Queue::queue_calculate_cost(Order order, std::vector<Status>& status_vector){
	unsigned int temp_cost = 0;
	unsigned int lowest_cost = 10000;
	int elevator_ID = -1;

	for(std::vector<Status>::iterator it = status_vector.begin(); it != status_vector.end();++it){
		Status status_it = *it;
		//Check status on the elevators that are not out of order.
		if (status_it.out_of_order != 1){ 
			temp_cost = abs(order.floor - status_it.floor)*10; //Rewrite cost calculation!!!!
			if (temp_cost < lowest_cost){
				lowest_cost = temp_cost;
				elevator_ID = status_it.elevator_ID;
			}

		}
	}
	return elevator_ID;
}
*/


void Queue::queue_write_order_matrix(){
	std::ofstream file;
	file.open("backup_file.txt");
	
	if (file.is_open()){

		for (int i=0;i<N_FLOORS;i++){
			for (int j=0;j<N_BUTTONS;j++){
				file << this->order_matrix[i][j].active_button << this->order_matrix[i][j].elevator_ID << "&";
			}
		}
		file.close();
	}
	else
		std::cout << "Unable to open file at queue_write_order_matrix" << std::endl;
}


//--------------------------------------------------------------------------------------------------
//Public member functions
//----------------------------------------------------------------------------------------------------

/*
//Not finished!
void Queue::queue_read_order_matrix(){
	std::string line;
	std::vector<std::string> result;
	ifstream file;
	file.open("backup_file.txt");
	if (file.is_open()){
			while(getline(file,line,':')){
				result.push_back(line);
			}
			//this->order_matrix = string_to_order_matrix(result); //Funksjon fra network.h
	}
	else
		cout << "Unable to open file at queue_read_order_matrix" << endl;
}
*/






std::vector<std::vector<Queue_element> > Queue::queue_get_order_matrix(){
	return this->order_matrix;
} 

std::vector<std::vector<Queue_element> >* Queue::queue_get_order_matrix_ptr(){
	return this->order_matrix_ptr;
}

/*
void Queue::queue_merge_order_matrices(Queue queue_with_new_order_matrix){
	for (int i=0;i<N_FLOORS;i++){
		for (int j=0;j<N_BUTTONS;j++){

			if ((queue_with_new_order_matrix.order_matrix[i][j].elevator_ID != -1) && (this->order_matrix[i][j].elevator_ID == -1))
				this->order_matrix[i][j] = queue_with_new_order_matrix.order_matrix[i][j];
		}
	}
}
*/


void Queue::queue_print_order_matrix(std::vector<std::vector<Queue_element> > order_matrix){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	for (row = order_matrix.begin(); row!=order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			std::cout << col->active_button<< ":" << col->elevator_ID << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Queue::queue_print_order_matrix(){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			std::cout << col->active_button<< ":" << col->elevator_ID << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


std::vector<std::vector<Queue_element> > Queue::queue_add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order new_order, int elevator_ID){
	if (new_order.floor > N_FLOORS){
		std::cout << "Floor in new_order doesn't match number of floors in system" << std::endl;
		return order_matrix;
	}
	if (new_order.btn > N_BUTTONS){
		std::cout << "Button in new_order doesn't match number of buttons in system" << std::endl;
		return order_matrix;
	}

	if ((order_matrix.size() < new_order.floor)||(order_matrix[0].size() < new_order.btn)){
		std::cout << "Dimensions disagree in queue_add_order" << std::endl;
		return order_matrix;
	}

	order_matrix[new_order.floor][new_order.btn].active_button = 1;
	order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
	return order_matrix;
}

void Queue::queue_add_order(Order new_order, int elevator_ID){
	if (new_order.floor > N_FLOORS){
		std::cout << "Floor in new_order doesn't match number of floors in system" << std::endl;
		return ;
	}
	if (new_order.btn > N_BUTTONS){
		std::cout << "Button in new_order doesn't match number of buttons in system" << std::endl;
		return ;
	}
	this->order_matrix[new_order.floor][new_order.btn].active_button = 1;
	this->order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
}

/*
void Queue::queue_remove_order(Order order){
	this->order_matrix[order.floor][order.btn].active_button = 0;
	this->order_matrix[order.floor][order.btn].elevator_ID = -1;
}
*/


/*
void Queue::queue_assign_elevators_to_orders(std::vector<Elevator>& elevators){

	if (elevators == NULL){
		cout << "Cant assign empty elevators to orders in queue_assign_elevators_to_orders" << endl;
		return;
	}

	//Create a status_vector based on the input.
	vector<Status> status_vector;
	for (int e=0;e<N_ELEVATORS;e++){
		status iteration_status;
		iteration_status.dir = elvators[e].get_direction();
		iteration_status.floor = elevators[e].get_floor();
		iteration_status.elevator_ID = elevators[e].get_elevator_ID;
		iteration_status.out_of_order = elevators[e].get_out_of_order_status();
		status_vector.push_back(iteration_status);	
	}


	for (int e=0;e<N_ELEVATORS;e++){
		for (int i=0;i<N_FLOORS;i++){
			for(int j=0;j<N_BUTTONS;j++){
				if ((elevators[e].elevator_get_order_matrix_ptr()[i][j].active_button == 1) && (elevators[e].elevator_get_order_matrix_ptr()[i][j].elevator_ID == -1)){
					Order order_to_be_assigned;
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = j;

					elevators[e].elevator_get_order_matrix_ptr()[i][j].elevator_ID == queue_calculate_cost(order_to_be_assigned,status_vector);
				}
			}
		}
	}
}
*/



/*
void Queue::queue_reset_orders(Status status){
	if (this->order_matrix == NULL){
		cout << "Can't reset an empty order matrix" << endl;
		return;
	}

	for (int i=0;i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if ((this->order_matrix[i][j].active_button == 1)&&(this->order_matrix[i][j].elevator_ID == status.elevator_ID))
				this->order_matrix[i][j].elevator_ID = -1;
		}
	}	
}
*/


