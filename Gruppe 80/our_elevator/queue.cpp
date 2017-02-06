#include <iostream>
#include "queue.h"


using namespace std;

int main(){
	cout << "Halla" << endl;

	//Queue test(2,2);

	Queue_element test;
	test.active_button = 0;
}




Queue::Queue(unsigned int n_buttons, unsigned int n_floors){
	this->n_buttons = n_buttons;
	this->n_floors = n_floors;

	this->order_matrix = new Queue_element *[n_floors]{};

	for(int i=0;i<n_floors;i++){
		this->order_matrix[i] = new Queue_element [n_buttons]{};
	}

	for(int i=0;i<n_floors;i++){
		for(int j=0;j<n_buttons;j++){
			order_matrix[i][j].active_button = 0;
			order_matrix[i][j].elevator_ID = 0;
		}
	}
}




/*


void Queue::queue_add_order(Order new_order,unsigned int elevator_ID);


void Queue::queue_remove_order(Elevator &elevator);


Queue_element Queue::queue_get_order_matrix();


void Queue::queue_assign_elevators_to_orders(Elevator &elevators);


void Queue::queue_merge_order_matrices(Queue_element* new_order_matrix);


void Queue::queue_reset_orders(Elevator &elevator);
*/
