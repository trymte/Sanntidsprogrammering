#include <iostream>
#include <vector>
#include "queue.h"
#include "queue.cpp"
#include "const_struct_def.h"




int main(){
	Queue que;
	Queue que2;

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
	test_status.dir = D_Down;
	test_status.floor = 3;
	test_status.elevator_ID = 1;
	test_status.out_of_order = 0;


///////////////////////////////////////////////////////////
//Testing
///////////////////////////////////////////////////////////


	
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