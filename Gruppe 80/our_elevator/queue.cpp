
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "queue.h"
#include "elevator.h"
//#include "network.h"

using namespace std;

//Constructor and destructor

Queue::Queue(unsigned int n_floors,unsigned int n_buttons){
	this->order_matrix = new Queue_element *[n_floors];//{};

	for(int i=0;i<n_floors;i++){
		this->order_matrix[i] = new Queue_element [n_buttons];//{};
	}

	for(int i=0;i<n_floors;i++){
		for(int j=0;j<n_buttons;j++){
			order_matrix[i][j].active_button = 0;
			order_matrix[i][j].elevator_ID = -1;
		}
	}
}

Queue::~Queue(){
	if(this->order_matrix != NULL){
		for(int i = 0; i < N_FLOORS; i++){
			if (this->order_matrix[i] != NULL)
				delete this->order_matrix[i];
		}
		this->order_matrix = NULL;
		
	}
}


//Member function definitions

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

void Queue::queue_write_order_matrix(){
	ofstream file;
	file.open("backup_file.txt");
	if (file.is_open()){

		for (int i=0;i<this->n_floors;i++){
			for (int j=0;j<this->n_buttons;j++){
				file << this->order_matrix[i][j].active_button << ":" << this->order_matrix[i][j].elevator_ID << ";";
			}
			file << "\n";
		}
		file.close();
	}
	else
		cout << "Unable to open file at queue_write_order_matrix" << endl;
}


//Not finished!
void Queue::queue_read_order_matrix(){
	int row,col;
	string line;
	string act_but;
	string elev_ID;

	ifstream file;
	file.open("backup_file.txt");
	if (file.is_open()){
		//work in progess...
			


			/*
			while(getline(file,line)){
			string::iterator it;
			for(it=line.begin();it<line.end();it++){
				if ((elementshift == 0)&&(*it != ':'))
					act_but += *it;
				else if ((elementshift == 1)&&(*it != ';'))
					elev_ID += *it;
				else if (*it == ';')
					col += 1;
				else
					elementshift = 1;
			}
			cout << "Act_but: " << act_but << "  elev_ID: " << elev_ID << endl;
			
			this->order_matrix[row][col].active_button = atoi(act_but.c_str());
			this->order_matrix[row][col].elevator_ID = atoi(elev_ID.c_str());
			act_but = "";
			elev_ID = "";
			col = 0;
			row += 1;
			elementshift = 0;
			while_iterator += 1;
		*/
		
		
	}
	else
		cout << "Unable to open file at queue_read_order_matrix" << endl;
}


void Queue::queue_add_order(Order new_order, int elevator_ID){
	if (new_order.floor > this->n_floors){
		cout << "Floor in new_order doesn't match number of floors in system" << endl;
		return;
	}
	if (new_order.btn > this->n_buttons){
		cout << "Button in new_order doesn't match number of buttons in system" << endl;
		return;
	}
	this->order_matrix[new_order.floor][new_order.btn].active_button = 1;
	this->order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
}


Queue_element** Queue::queue_get_order_matrix(){
	return this->order_matrix;
} 


void Queue::queue_merge_order_matrices(Queue queue_with_new_order_matrix){//,Queue_element **new_order_matrix){ //Ta inn hele kø-objektet?
	//Check dimensions
	if ((queue_with_new_order_matrix.n_buttons != this->n_buttons) || (queue_with_new_order_matrix.n_floors != this->n_floors)){
		cout << "Matrix dimensions disagree in queue_merge_order_matrices" << endl;
		return;
	}

	for (int i=0;i<this->n_floors;i++){
		for (int j=0;j<this->n_buttons;j++){

			if ((queue_with_new_order_matrix.order_matrix[i][j].elevator_ID != -1) && (this->order_matrix[i][j].elevator_ID == -1))
				this->order_matrix[i][j] = queue_with_new_order_matrix.order_matrix[i][j];
		}
	}
}


void Queue::queue_print_order_matrix(){
	if (this->order_matrix == NULL){
		cout << "Can't print empty order matrix" << endl;
		return;
	}
	for (int i=0;i<this->n_floors;i++){
		for (int j=0;j<this->n_buttons;j++){
			cout << this->order_matrix[i][j].active_button << ":" << this->order_matrix[i][j].elevator_ID << "\t";
		}
		cout << endl;
	}
	cout << endl;
}


void Queue::queue_remove_order(Order order){
	this->order_matrix[order.floor][order.btn].active_button = 0;
	this->order_matrix[order.floor][order.btn].elevator_ID = -1;
}

/*


void Queue::queue_assign_elevators_to_orders(Elevator &elevators){
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



