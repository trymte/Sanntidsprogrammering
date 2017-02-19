#pragma once

#include <vector>
#include "elevator.h"
#include "const_struct_def.h"



class Queue{
private:
	std::vector<std::vector<Queue_element> > order_matrix;
	std::vector<std::vector<Queue_element> > *order_matrix_ptr;

	static unsigned int queue_calculate_cost(Order order, std::vector<Status>& status_vector);
	

public:
	Queue();

	Queue(unsigned int n_floors,unsigned int n_buttons);

	~Queue();

	static std::vector<std::vector<Queue_element> > queue_add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID);

	void queue_add_order(Order new_order, int elevator_ID);

	std::vector<std::vector<Queue_element> > queue_get_order_matrix();

	std::vector<std::vector<Queue_element> >* queue_get_order_matrix_ptr();

	static std::vector<std::vector<Queue_element> > queue_merge_order_matrices(std::vector <std::vector <Queue_element> > &order_matrix_1,std::vector <std::vector <Queue_element> > &order_matrix_2);

	void queue_merge_order_matrices(Queue queue_with_new_order_matrix); //Endre til UML std

	void queue_write_order_matrix();
	
	void queue_read_order_matrix();

	static std::vector<std::vector<Queue_element> > queue_remove_order(std::vector <std::vector <Queue_element> > &order_matrix,Order order);

	void queue_remove_order(Order order);

	static void queue_print_order_matrix(std::vector<std::vector<Queue_element> > order_matrix);

	void queue_print_order_matrix();
	
	//void assign_elevators_to_orders(Elevator &elevators);

	//static void queue_assign_elevators_to_orders(std::vector<Elevator>& elevators);

	void queue_reset_orders(Status status);

};

