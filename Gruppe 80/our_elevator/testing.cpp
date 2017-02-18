#include <iostream>
#include <vector>
#include "queue.h"
#include "queue.cpp"
#include "const_struct_def.h"




int main(){
	Queue que;
	std::vector <std::vector <Queue_element> > order_matrix;


	Queue::queue_print_order_matrix(que.queue_get_order_matrix());
	/*

	std::vector <std::vector <Queue_element> > order_matrix;

	//Constructor
	for (int i=0;i<N_FLOORS;i++){
		std::vector<Queue_element> rowvector;
		for(int j=0;j<N_BUTTONS;j++){
			Queue_element init_element;
			init_element.active_button = 0;
			init_element.elevator_ID = -1;
			rowvector.push_back(init_element);
		}
		order_matrix.push_back(rowvector);
	}


	//Print
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	for (row = order_matrix.begin(); row!=order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			std::cout << col->active_button<< ":" << col->elevator_ID << "\t";
		}
		std::cout << std::endl;
	}
	*/
}
