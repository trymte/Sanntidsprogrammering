#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

#include "queue.h"
//#include "elevator.h"
//#include "network.h"



using namespace std;

int main(){
	
	cout << "jeg lever" << endl;

	Queue A(N_FLOORS,N_BUTTONS);

	cout << "A-matrix" << endl;
	A.queue_print_order_matrix();

	Order new_order;
	new_order.floor = 2;
	new_order.btn = B_HallUp;

	Order new_order2;
	new_order2.floor = 3;
	new_order.btn = B_HallDown;

	Queue B(N_FLOORS,N_BUTTONS);

	B.queue_add_order(new_order,2);
	//B.queue_add_order(new_order2,2);
	cout << "B-matrix:" << endl;
	B.queue_print_order_matrix();

	A.queue_merge_order_matrices(B);
	cout << "A-matrix after merge with B:" << endl;
	A.queue_print_order_matrix();

	Status test_status_1;
	test_status_1.dir = D_Up;
	test_status_1.floor = 2;
	test_status_1.elevator_ID = 2;
	test_status_1.out_of_order = 0;

	Status test_status_2;
	test_status_2.dir = D_Down;
	test_status_2.floor = 1;
	test_status_2.elevator_ID = 3;
	test_status_2.out_of_order = 0;

	A.queue_remove_order(new_order);
	cout << "A-matrix after removed order" << endl;
	A.queue_print_order_matrix();



	//Status_vector
	vector<Status> status_vector;
	status_vector.push_back(test_status_1);
	status_vector.push_back(test_status_2);

	cout << "Best elevator_ID: " << A.queue_calculate_cost(new_order, status_vector) << endl;



	//Backup of order_matrix
	A.queue_write_order_matrix();
	A.queue_read_order_matrix();

}





//Constructor and destructor

Queue::Queue(unsigned int n_floors,unsigned int n_buttons){
	this->n_buttons = n_buttons;
	this->n_floors = n_floors;

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
	if(order_matrix != NULL){
		for(int i = 0; i < n_floors; i++){
			delete [] order_matrix[i];
		delete [] order_matrix;
		}
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

void Queue::queue_read_order_matrix(){
	int row = 0;
	int col = 0;
	string line;
	string act_but;
	string elev_ID;

	ifstream file;
	file.open("backup_file.txt");
	if (file.is_open()){
		while(getline(file,line,';')){
			//Work in progress
		}
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

//void Queue::queue_assign_elevators_to_orders(Elevator &elevators);


void Queue::queue_reset_orders(Status status){
	for (int i=0;i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if ((this->order_matrix[i][j].active_button == 1)&&(this->order_matrix[i][j].elevator_ID == status.elevator_ID))
				this->order_matrix[i][j].elevator_ID = -1;
		}
	}	

}



