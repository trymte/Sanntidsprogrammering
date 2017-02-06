#include <iostream>
#include "queue.h"
#include "network.h"


using namespace std;

int main(){

	Queue A(3,3);
	cout << A.test_get_queue_element(2,0).active_button << endl;

	A.queue_print_order_matrix();

	Order new_order;

	new_order.floor = 2;
	new_order.btn = B_HallUp;
	A.queue_add_order(new_order,2);
	A.queue_print_order_matrix();

	

}




Queue::Queue(unsigned int n_buttons, unsigned int n_floors){
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


/*

void Queue::queue_remove_order(Elevator &elevator);


Queue_element Queue::queue_get_order_matrix(){} //Foreslår å bruke friend på de klassene som trenger order_matrix



void Queue::queue_assign_elevators_to_orders(Elevator &elevators);


void Queue::queue_merge_order_matrices(Queue_element* new_order_matrix);


void Queue::queue_reset_orders(Elevator &elevator);
*/

void Queue::queue_print_order_matrix(){
	for (int i=0;i<this->n_floors;i++){
		for (int j=0;j<this->n_buttons;j++){
			cout << this->order_matrix[i][j].active_button << ":" << this->order_matrix[i][j].elevator_ID << "\t";
		}
		cout << endl;
	}
	cout << endl;

}