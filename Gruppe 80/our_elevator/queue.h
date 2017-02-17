#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include "elevator.h"


//Constants to be moved
const unsigned int N_FLOORS = 4;
const unsigned int N_BUTTONS = 3;
const unsigned int N_ELEVATORS = 2;



struct Queue_element{
	bool active_button;
	int elevator_ID;
};

struct Order{
	unsigned int floor;
	Button btn;
};




class Queue{
private:
	Queue_element** order_matrix;

	unsigned int queue_calculate_cost(Order order, std::vector<Status>& status_vector);
	void queue_write_order_matrix();
	void queue_read_order_matrix();

public:
	Queue(unsigned int n_floors,unsigned int n_buttons);
	~Queue();

	void queue_add_order(Order new_order,int elevator_ID);
	Queue_element** queue_get_order_matrix();	
	void queue_merge_order_matrices(Queue queue_with_new_order_matrix); //Endre til UML std
	void queue_print_order_matrix();
	void assign_elevators_to_orders(Elevator &elevators);



	void queue_remove_order(Order order);
//	static void queue_assign_elevators_to_orders(Elevator &elevators);

	void queue_reset_orders(Status status);

};

#endif