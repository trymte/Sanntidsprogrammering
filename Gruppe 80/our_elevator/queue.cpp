
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
	Queue_element init_element;
	init_element.active_button = 0;
	init_element.elevator_ID = -1;
	for (int i=0;i<N_FLOORS;i++){
		std::vector<Queue_element> rowvector;
		for(int j=0;j<N_BUTTONS;j++){
			rowvector.push_back(init_element);
		}
		order_matrix.push_back(rowvector);
	}	
	this->order_matrix_ptr = &order_matrix;
}


Queue::Queue(unsigned int n_floors,unsigned int n_buttons){
	std::vector<std::vector<Queue_element> > temp;
	this->order_matrix = temp;
	Queue_element init_element;
	init_element.active_button = 0;
	init_element.elevator_ID = -1;
	for (int i=0;i<n_floors;i++){
		std::vector<Queue_element> rowvector;
		for(int j=0;j<n_buttons;j++){
			
			rowvector.push_back(init_element);
		}
		order_matrix.push_back(rowvector);
	}
	this->order_matrix_ptr = &order_matrix;
}
//Forslag: Trur det går bra med bare ein konstruktør for queue, sidan N_FLOORS og N_BUTTONS er globale, og dei to konstruktørane er ganske like :) - Trym
//Det kan vi gjøre. Beholde den øverste da? :) 

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

unsigned int Queue::calculate_cost(Order order, std::vector<Status>& status_vector){
	unsigned int temp_cost = 0;
	unsigned int lowest_cost = 10000;
	int elevator_ID = -1;
	Status status_it;

	for(std::vector<Status>::iterator it = status_vector.begin(); it != status_vector.end();++it){
		status_it = *it;
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


//--------------------------------------------------------------------------------------------------
//Public member functions
//----------------------------------------------------------------------------------------------------
void Queue::write_order_matrix(){
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

//Not finished!
void Queue::read_order_matrix(){
	std::string line;
	std::vector<std::string> result;
	std::ifstream file;
	file.open("backup_file.txt");
	if (file.is_open()){
			while(getline(file,line,':')){
				result.push_back(line);
			}
			//this->order_matrix = string_to_order_matrix(result); //Funksjon fra network.h
	}
	else
		std::cout << "Unable to open file at queue_read_order_matrix" << std::endl;
}

std::vector<std::vector<Queue_element> > Queue::get_order_matrix(){
	return this->order_matrix;
} 

std::vector<std::vector<Queue_element> >* Queue::get_order_matrix_ptr(){
	return this->order_matrix_ptr;
}





std::vector<std::vector<Queue_element> > Queue::merge_order_matrices(std::vector <std::vector <Queue_element> > &order_matrix_1,std::vector <std::vector <Queue_element> > &order_matrix_2){
	if ((order_matrix_1.size() != order_matrix_2.size())||(order_matrix_1[0].size() != order_matrix_2[0].size())){
		std::cout << "Dimensions disagree in queue_to_be_merged" << std::endl;
		return order_matrix_1;
	}

	int rows = order_matrix_1.size();
	int cols = order_matrix_1[0].size();

	for (int i = 0;i<rows;i++){
		for (int j=0;j<cols;j++){
			if ((order_matrix_1[i][j].elevator_ID == -1) && (order_matrix_2[i][j].elevator_ID != -1)){

				order_matrix_1[i][j].active_button = order_matrix_2[i][j].active_button;
				order_matrix_1[i][j].elevator_ID = order_matrix_2[i][j].elevator_ID;
			}
		}
	}

	return order_matrix_1;
}


void Queue::merge_order_matrices(Queue queue_to_be_merged){
	if ((this->order_matrix.size() != queue_to_be_merged.order_matrix.size())||(this->order_matrix[0].size() != queue_to_be_merged.order_matrix[0].size())){
		std::cout << "Dimensions disagree in queue_to_be_merged" << std::endl;
		return;
	}

	int rows = this->order_matrix.size();
	int cols = this->order_matrix[0].size();

	for (int i = 0;i<rows;i++){
		for (int j=0;j<cols;j++){
			if ((this->order_matrix[i][j].elevator_ID == -1) && (queue_to_be_merged.order_matrix[i][j].elevator_ID != -1)){
				this->order_matrix[i][j].active_button = queue_to_be_merged.order_matrix[i][j].active_button;
				this->order_matrix[i][j].elevator_ID = queue_to_be_merged.order_matrix[i][j].elevator_ID;
			}
		}
	}
}



void Queue::print_order_matrix(std::vector<std::vector<Queue_element> > order_matrix){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	std::cout << std::endl;
	for (row = order_matrix.begin(); row!=order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			std::cout << col->active_button<< ":" << col->elevator_ID << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Queue::print_order_matrix(){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	std::cout << std::endl;
	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			std::cout << col->active_button<< ":" << col->elevator_ID << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


std::vector<std::vector<Queue_element> > Queue::add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID){
	if (new_order.floor > N_FLOORS){
		std::cout << "Floor in new_order doesn't match number of floors in system" << std::endl;
		return order_matrix;
	}
	if (new_order.btn > N_BUTTONS){
		std::cout << "Button in new_order doesn't match number of buttons in system, " << new_order.btn << " > " << N_BUTTONS <<  std::endl;
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

void Queue::add_order(Order new_order, int elevator_ID){
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


void Queue::remove_order(Order order){
	this->order_matrix[order.floor][order.btn].active_button = 0;
	this->order_matrix[order.floor][order.btn].elevator_ID = -1;
}

std::vector<std::vector<Queue_element> > Queue::remove_order(std::vector <std::vector <Queue_element> > &order_matrix,Order order){
	if ((order_matrix.size() < order.floor)||(order_matrix[0].size() < order.btn)){
		std::cout << "Dimensions disagree in queue_remove_order" << std::endl;
		return order_matrix;
	}
	order_matrix[order.floor][order.btn].active_button = 0;
	order_matrix[order.floor][order.btn].elevator_ID = -1;
	return order_matrix;
}

/*
std::vector<std::vector<Queue_element> > assign_elevators_to_orders(std::vector<Elevator> &elevators){

	if (elevators.size() == 0){
		cout << "Cant assign empty elevators to orders in queue_assign_elevators_to_orders" << endl;
		return;
	}

	//Create a status_vector based on the input.
	std::vector<Status> status_vector;
	std::vector<Elevator>::iterator elevator_it;
	status iteration_status;
	for (elevator_it = elevators.begin();elevator_it != elevators.end();++elevator_it){
		iteration_status.dir = *elevator_it.get_direction();
		iteration_status.floor = *elevator_it.get_floor();
		iteration_status.elevator_ID = *elevator_it.get_elevator_ID;
		iteration_status.out_of_order = *elevator_it.get_out_of_order_status();
		status_vector.push_back(iteration_status);	
	}

	//Create a order_matrix that contains all the orders assigned to an elevator
	std::vector<std::vector<Queue_element> > assigned_order_matrix;
	assigned_order_matrix = vector_init();
	Order order_to_be_assigned;
	int assigned_elevator = -1;

	for(elevator_it = elevators.begin();elevator_it != elevators.end();++elevator_it){
		for (int i=0;i<N_FLOORS;i++){
			for(int j=0;j<N_BUTTONS;j++){
				//If an order in an order_matrix in elevators is not found in assigned_order_matrix, add it.
				if ((assigned_order_matrix[i][i].active_button == 0)&&(*it->get_order_matrix_prt()[i][j].active_button == 1)){
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = j;
					assigned_order_matrix = Queue::queue_add_order(assigned_order_matrix,order_to_be_assigned,*it->get_order_matrix_ptr()[i][j].elevator_ID);
				}


				//Find elevator with lowest cost and add order to assigned_order_matrix
				if ((elevator_it->get_order_matrix_ptr()[i][j].active_button == 1) && (elevator_it->get_order_matrix_ptr()[i][j].elevator_ID == -1)){
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = j;
					assigned_elevator = Queue::queue_calculate_cost(order_to_be_assigned,status_vector);
					assigned_order_matrix = Queue::queue_add_order(assigned_order_matrix, order_to_be_assigned,assigned_elevator);

				}
			}
		}
	}

	return assigned_order_matrix;
}
*/




void Queue::reset_orders(Status status){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			if ((col->active_button == 1)&&(col->elevator_ID == status.elevator_ID))
				col->elevator_ID = -1;
		}
	}
}



Order Queue::get_next_order(int elevator_ID){
	Order next_order;
	next_order.floor = 0;
	next_order.btn = B_HallDown;

	for (int floor = 0; floor<N_FLOORS;floor++){
		for (int btn = 0;btn<N_BUTTONS;btn++){
			if ((this->order_matrix[floor][btn].active_button == 1)&&(this->order_matrix[floor][btn].elevator_ID == elevator_ID)){
				next_order.floor = floor;
				switch(btn){
					case 0:
						next_order.btn = B_HallUp;
						break;
					case 1:
						next_order.btn = B_HallDown;
						break;
					case 2:
						next_order.btn = B_Cab;
						break;
				}
				return next_order;
			}
		}
	}	
}