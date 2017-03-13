#pragma once

#include "elevator.h"


class Queue{
private:
	std::vector<std::vector<Queue_element> > order_matrix;

	static void add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID);

	static unsigned int calculate_cost(Order order, Status status);

	static unsigned int get_lowest_cost_elevator(Order order, std::vector<Status>& status_vector, std::vector<Elevator*> elevators);
	
public:
	Queue();

	~Queue();


	static std::vector<std::vector<Queue_element> > assign_elevators_to_orders(std::vector<Elevator*> elevators, int elevator_ID);

//------------------------------------------------------------------------------------------------------------
//		Get functions
//------------------------------------------------------------------------------------------------------------

	Order get_next_order(int elevator_ID);

	std::vector<std::vector<Queue_element> > get_order_matrix(){return this->order_matrix;}

	std::vector<std::vector<Queue_element> >* get_order_matrix_ptr(){return &this->order_matrix;}

//------------------------------------------------------------------------------------------------------------

	void add_order(Order new_order, int elevator_ID);

	void remove_order(Order order);

	static void reset_orders(std::vector <std::vector <Queue_element> > &order_matrix, Status status);

	void reset_orders(Status status);

//------------------------------------------------------------------------------------------------------------
//		Order matrix backup file functions
//------------------------------------------------------------------------------------------------------------

	void write_order_matrix_to_file();
	
	void read_order_matrix_from_file();

};