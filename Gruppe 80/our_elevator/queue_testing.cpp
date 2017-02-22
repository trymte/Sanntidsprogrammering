#include <iostream>
#include <vector>
#include "queue.h"




int main(){
	Queue que;
	Queue que2;

	Elevator elev1;
	Elevator elev2;

	Order test_order;
	test_order.floor = 2;
	test_order.btn = B_HallDown;

	Order test_order2;
	test_order2.floor = 3;
	test_order2.btn = B_HallDown;

	Status test_status;
	test_status.dir = D_Stop;
	test_status.floor = 2;
	test_status.elevator_ID = 3;
	test_status.out_of_order = 0;

	Status test_status2;
	test_status2.dir = D_Down;
	test_status2.floor = 1;
	test_status2.elevator_ID = 1;
	test_status2.out_of_order = 0;




//	std::cout << elev1->get_order_matrix_ptr[1][1] << std::endl;

/*
///////////////////////////////////////////////////////////
//Testing av assign elevators to orders
///////////////////////////////////////////////////////////
	

	std::vector<std::vector<Queue_element> > test_order_matrix1 = vector_init();
	std::vector<std::vector<Queue_element> > *test_order_matrix1_ptr = &test_order_matrix1;
	std::vector<std::vector<Queue_element> > test_order_matrix2 = vector_init(); 
	std::vector<std::vector<Queue_element> > *test_order_matrix2_ptr = &test_order_matrix2;

	test_order_matrix1[2][2].active_button = 1;
	test_order_matrix1[2][2].elevator_ID = -1;

	test_order_matrix2[1][1].active_button = 1;
	test_order_matrix2[1][1].elevator_ID = -1;

	std::cout << "Order matrix in elev1:" << std::endl;
	Queue::print_order_matrix(test_order_matrix1);

	std::cout << "Order matrix in elev2:" << std::endl;
	Queue::print_order_matrix(test_order_matrix2);

	elev1.set_elevator_order_matrix(test_order_matrix1_ptr);
	elev2.set_elevator_order_matrix(test_order_matrix2_ptr);

	elev1.set_elevator_status(test_status);
	elev2.set_elevator_status(test_status2);

	std::vector<Elevator> elevators;
	elevators.push_back(elev1);
	elevators.push_back(elev2);

	std::vector<std::vector<Queue_element> > assigned_order_matrix;

	assigned_order_matrix = Queue::assign_elevators_to_orders(elevators);

	std::cout << "Assigned order matrix:" << std::endl;
	Queue::print_order_matrix(assigned_order_matrix);
*/


	
}


/*
Vector pointers
std::vector<std::vector <Queue_element> > test_vector;
test_vector = vector_init();

std::vector<std::vector <Queue_element> > *test_vector_ptr;
test_vector_ptr = &test_vector;


std::vector<std::vector <Queue_element> > test_vector2;
Make test_vector2 equal to waht test_vector_ptr points at.
test_vector2 = *test_vector_ptr;
std::cout << test_vector2[1][1].active_button << std::endl;
*/