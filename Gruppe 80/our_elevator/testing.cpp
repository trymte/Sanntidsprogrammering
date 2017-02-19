#include <iostream>
#include <vector>
#include "queue.h"
#include "queue.cpp"
#include "const_struct_def.h"




int main(){
/////////////////////////////////////////////////////////////
//Prinsipp testing
/////////////////////////////////////////////////////////////
/*
	Queue queue;
	std::vector<std::vector<Queue_element> > order_matrix;
	
	std::vector<std::vector<Queue_element> > *order_matrix_ptr = queue.queue_get_order_matrix_ptr();



	order_matrix = queue.queue_get_order_matrix();
	std::cout << order_matrix[2][2].elevator_ID << std::endl;
	order_matrix[2][2].elevator_ID = 2;
	std::cout << order_matrix[2][2].elevator_ID << std::endl;

*/

/////////////////////////////////////////////////////////////
//Funksjonstesing
/////////////////////////////////////////////////////////////

	Queue que;
	
	Queue::queue_print_order_matrix(que.queue_get_order_matrix()); //Dette fungerer ikke med call by reference..

	Order test_order;
	test_order.floor = 2;
	test_order.btn = B_HallUp;

	que.queue_add_order(test_order,3);
	que.queue_print_order_matrix();
	que.queue_write_order_matrix();


	std::vector<std::vector<Queue_element> > order_matrix;
	order_matrix = Queue::queue_add_order(order_matrix,test_order,2);
	Queue::queue_print_order_matrix(order_matrix);



}
