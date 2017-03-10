#pragma once

#include "elevator.h"




class Queue{
private:
	std::vector<std::vector<Queue_element> > order_matrix;


	
public:
	Queue();

	Queue(unsigned int n_floors,unsigned int n_buttons);

	~Queue();

	static unsigned int calculate_cost(Order order, Status status);

	static unsigned int get_lowest_cost_elevator(Order order, std::vector<Status>& status_vector);

	static void add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID);

	void add_order(Order new_order, int elevator_ID);

	static void remove_order(std::vector <std::vector <Queue_element> > &order_matrix,Order order);

	void remove_order(Order order);

	void reset_orders(Status status);

	static void reset_orders(std::vector <std::vector <Queue_element> > &order_matrix, Status status);

	Order get_next_order(int elevator_ID);

	std::vector<std::vector<Queue_element> > get_order_matrix(){return this->order_matrix;}

	std::vector<std::vector<Queue_element> >* get_order_matrix_ptr(){return &this->order_matrix;}

	static std::vector<std::vector<Queue_element> > assign_elevators_to_orders(std::vector<Elevator*> elevators, int elevator_ID);

	void write_order_matrix_to_file();
	
	void read_order_matrix_from_file();

};



