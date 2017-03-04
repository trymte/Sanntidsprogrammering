#pragma once

#include "const_struct_def.h"
#include "elevator.h"




class Queue{
private:
	std::vector<std::vector<Queue_element> > order_matrix;
	std::vector<std::vector<Queue_element> > *order_matrix_ptr;

	
public:
	Queue();

	Queue(unsigned int n_floors,unsigned int n_buttons);

	~Queue();

	static unsigned int calculate_cost(Order order, std::vector<Status>& status_vector);

	static void add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID);

	void add_order(Order new_order, int elevator_ID);

	std::vector<std::vector<Queue_element> > get_order_matrix();

	std::vector<std::vector<Queue_element> >* get_order_matrix_ptr();

	static std::vector<std::vector<Queue_element> > merge_order_matrices(std::vector <std::vector <Queue_element> > &order_matrix_1,std::vector <std::vector <Queue_element> > &order_matrix_2);

	void merge_order_matrices(Queue queue_with_new_order_matrix); 

	void write_order_matrix();
	
	void read_order_matrix();

	static void remove_order(std::vector <std::vector <Queue_element> > &order_matrix,Order order);

	void remove_order(Order order);

	static void print_order_matrix(std::vector<std::vector<Queue_element> > order_matrix);

	void print_order_matrix();

	void reset_orders(Status status);

	static void reset_orders(std::vector <std::vector <Queue_element> > &order_matrix, Status status);

	Order get_next_order(int elevator_ID);

	std::vector<std::vector<Queue_element> > assign_elevators_to_orders(std::vector<Elevator> &elevators);

};



