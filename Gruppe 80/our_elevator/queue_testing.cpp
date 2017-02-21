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
//Class functions:
	Queue que;
	Queue que2;

	Order test_order;
	test_order.floor = 2;
	test_order.btn = B_HallUp;

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

	
/*
	std::cout << "Order_matrix after added order:" << std::endl;
	que.queue_add_order(test_order,3);
	que.queue_print_order_matrix();

	std::cout << "order_matrix after reset_orders: " << std::endl;
	que.queue_reset_orders(test_status);
	que.queue_print_order_matrix();

	std::cout << "Testing order matrix merge" << std::endl;
	que.queue_add_order(test_order,2);
	que2.queue_add_order(test_order2,3);
	std::cout << "Matrix 1: " << std::endl;
	que.queue_print_order_matrix();
	std::cout << "Matrix 2: " << std::endl;
	que2.queue_print_order_matrix();

	que.queue_merge_order_matrices(que2);
	std::cout << "Matrices merged: " << std::endl;
	que.queue_print_order_matrix();
*/


/*
//Static functions:
	std::cout << "Static functions testing" << std::endl;

	std::vector<std::vector<Queue_element> > test_order_matrix;
	std::vector<std::vector<Queue_element> > test_order_matrix_2;
	std::vector<std::vector<Queue_element> > test_order_matrix_3;
	
	test_order_matrix = que.queue_get_order_matrix();
	test_order_matrix_2 = que.queue_get_order_matrix();
	

	test_order_matrix = Queue::queue_add_order(test_order_matrix, test_order,2);
	
	test_order_matrix_2 = Queue::queue_add_order(test_order_matrix_2, test_order2,3);

	std::cout << "Matrix 1: " << std::endl;
	Queue::queue_print_order_matrix(test_order_matrix);

	std::cout << "Matrix 2: " << std::endl;
	Queue::queue_print_order_matrix(test_order_matrix_2);


	test_order_matrix = Queue::queue_merge_order_matrices(test_order_matrix,test_order_matrix_2);
	Queue::queue_print_order_matrix(test_order_matrix);

	test_order_matrix_3 = Queue::queue_merge_order_matrices(test_order_matrix_3, test_order_matrix);
*/
}
