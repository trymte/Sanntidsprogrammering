#include <iostream>
#include <vector>
#include "const_struct_def.h"


int main(){
	std::vector<std::vector <Queue_element> > test_vector;
	test_vector = vector_init();

	std::vector<std::vector <Queue_element> > *test_vector_ptr;
	test_vector_ptr = &test_vector;


	std::vector<std::vector <Queue_element> > test_vector2;
	//Make test_vector2 equal to waht test_vector_ptr points at.
	test_vector2 = *test_vector_ptr;
	std::cout << test_vector2[1][1].active_button << std::endl;

}