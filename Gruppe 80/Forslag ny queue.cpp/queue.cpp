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
	Queue A(N_FLOORS,N_BUTTONS);
/*
	cout << "A-matrix" << endl;
	A.get_order_matrix().print_order_matrix();

	Order new_order;
	new_order.floor = 2;
	new_order.btn = B_HallUp;

	Order new_order2;
	new_order2.floor = 3;
	new_order.btn = B_HallDown;

	Queue B(N_FLOORS,N_BUTTONS);

	B.get_order_matrix().add_order(new_order,2);
	B.get_order_matrix().add_order(new_order2,2);
	cout << "B-matrix:" << endl;
	B.get_order_matrix().print_order_matrix();



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

	A.queue_reset_orders(test_status_1);
	cout << "A-matrix after reset_orders" << endl;
	A.queue_print_order_matrix();



	//Status_vector
	vector<Status> status_vector;
	status_vector.push_back(test_status_1);
	status_vector.push_back(test_status_2);

	cout << "Best elevator_ID: " << A.queue_calculate_cost(new_order, status_vector) << endl;



	//Backup of order_matrix
	A.queue_write_order_matrix();
	A.queue_read_order_matrix();
*/
}

///////////////////////////////////////////////////////////////
//Order_matrix class functions:
///////////////////////////////////////////////////////////////
Order_matrix::Order_matrix(){
	this->order_matrix_ptr = new Queue_element *[N_FLOORS];
	for(int i=0;i<N_FLOORS;i++){
		this->order_matrix_ptr[i] = new Queue_element [N_BUTTONS];//{};
	}

	for(int i=0;i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			order_matrix_ptr[i][j].active_button = 0;
			order_matrix_ptr[i][j].elevator_ID = -1;
		}
	}
}

Order_matrix::Order_matrix(unsigned int n_floors, unsigned int n_buttons){

	this->order_matrix_ptr = new Queue_element *[n_floors];
	for(int i=0;i<n_floors;i++){
		this->order_matrix_ptr[i] = new Queue_element [n_buttons];//{};
	}

	for(int i=0;i<n_floors;i++){
		for(int j=0;j<n_buttons;j++){
			order_matrix_ptr[i][j].active_button = 0;
			order_matrix_ptr[i][j].elevator_ID = -1;
		}
	}
}

Order_matrix::~Order_matrix(){
	if(this->order_matrix_ptr != NULL){
		for(int i = 0; i < N_FLOORS; i++){
			if (this->order_matrix_ptr[i] != NULL)
				delete this->order_matrix_ptr[i];
		}
		this->order_matrix_ptr = NULL;
	}
}


void Order_matrix::add_order(Order new_order, int elevator_ID){
	if (new_order.floor > N_FLOORS){
		cout << "Floor in new_order doesn't match number of floors in system" << endl;
		return;
	}
	if (new_order.btn > N_BUTTONS){
		cout << "Button in new_order doesn't match number of buttons in system" << endl;
		return;
	}
	this->order_matrix_ptr[new_order.floor][new_order.btn].active_button = 1;
	this->order_matrix_ptr[new_order.floor][new_order.btn].elevator_ID = elevator_ID;

}

Queue_element** Order_matrix::get_order_matrix_ptr(){
	return this->order_matrix_ptr;
}


void Order_matrix::merge_order_matrices(Order_matrix new_order_matrix){

	for (int i=0;i<N_FLOORS;i++){
		for (int j=0;j<N_BUTTONS;j++){

			if ((new_order_matrix.order_matrix_ptr[i][j].elevator_ID != -1) && (this->order_matrix_ptr[i][j].elevator_ID == -1))
				this->order_matrix_ptr[i][j] = new_order_matrix.order_matrix_ptr[i][j];
		}
	}
}

void Order_matrix::print_order_matrix(){
	if (this->order_matrix_ptr == NULL){
		cout << "Can't print empty order matrix" << endl;
		return;
	}

	for (int i=0;i<N_FLOORS;i++){
		for (int j=0;j<N_BUTTONS;j++){
			cout << this->order_matrix_ptr[i][j].active_button << ":" << this->order_matrix_ptr[i][j].elevator_ID << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Order_matrix::remove_order(Order order){
	this->order_matrix_ptr[order.floor][order.btn].active_button = 0;
	this->order_matrix_ptr[order.floor][order.btn].elevator_ID = -1;
}


void Order_matrix::reset_orders(Status status){
	if (this->order_matrix_ptr == NULL){
		cout << "Can't reset an empty order matrix" << endl;
		return;
	}

	for (int i=0;i<N_FLOORS;i++){
		for(int j=0;j<N_BUTTONS;j++){
			if ((this->order_matrix_ptr[i][j].active_button == 1)&&(this->order_matrix_ptr[i][j].elevator_ID == status.elevator_ID))
				this->order_matrix_ptr[i][j].elevator_ID = -1;
		}
	}	
}

void Order_matrix::write_order_matrix(){
	ofstream file;
	file.open("backup_file.txt");
	if (file.is_open()){

		for (int i=0;i<N_FLOORS;i++){
			for (int j=0;N_BUTTONS;j++){
				file << this->order_matrix_ptr[i][j].active_button << ":" << this->order_matrix_ptr[i][j].elevator_ID << ";";
			}
			file << "\n";
		}
		file.close();
	}
	else
		cout << "Unable to open file at queue_write_order_matrix" << endl;
}

void Order_matrix::read_order_matrix(){
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
		cout << "Unable to open file at read_order_matrix" << endl;
}







///////////////////////////////////////////////////////////////
//Queue class functions:
///////////////////////////////////////////////////////////////
//Constructor and destructor

Queue::Queue(unsigned int n_floors,unsigned int n_buttons){
	this->n_buttons = n_buttons;
	this->n_floors = n_floors;

	Order_matrix new_order_matrix(n_floors,n_buttons);
	this->order_matrix = new_order_matrix;
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

Order_matrix Queue::get_order_matrix(){
	return this->order_matrix;
}
/*
//IKKE TESTET ENDA, FÅR LITT FOR MANGE ERROR I elevator.h, tester senere!
void Queue::queue_assign_elevators_to_orders(Elevator &elevators){
	if (elevators == NULL){
		cout << "Cant assign empty elevators to orders in queue_assign_elevators_to_orders" << endl;
		return;
	}

	//Create a status_vector based on the input.
	vector<Status> status_vector;
	for (int e=0;e<N_ELEVATORS;e++){

		//Kanskje lage en funksjon som gjør dette.
		status iteration_status;
		iteration_status.dir = elvators[e].get_direction();
		iteration_status.floor = elevators[e].get_floor();
		iteration_status.elevator_ID = elevators[e].get_elevator_ID;
		iteration_status.out_of_order = elevators[e].get_out_of_order_status();
		status_vector.push_back(iteration_status);	
		//
	}

	//Every elevator get their orders assigned
	for (int e=0;e<N_ELEVATORS;e++){
		for (int i=0;i<N_FLOORS;i++){
			for(int j=0;j<N_BUTTONS;j++){
				if ((elevators[e].elevator_get_order_matrix_ptr()[i][j].active_button == 1) && (elevators[e].elevator_get_order_matrix_ptr()[i][j].elevator_ID != 1)){
					Order order_to_be_assigned;
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = j;

					elevators[e].elevator_get_order_matrix_ptr()[i][j].elevator_ID == queue_calculate_cost(order_to_be_assigned,status_vector);
				}
			}
		}
	}

	//Merge the order matrixes together so all elevators have the same order_matrix
	
	for (int e=0;e<N_ELEVATORS;e++){
		//Create new matrix to be merged with elevator order matrix.
		Queue_element** complete_order_matrix_ptr;
		complete_order_matrix = new Queue_element *[N_FLOORS];
		for(int i=0;i<N_FLOORS;i++){
			complete_order_matrix[i] = new Queue_element [N_BUTTONS];
		}

		complete_order_matrix

	}

}
*/



