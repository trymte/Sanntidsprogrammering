#include <vector>
#include <stdlib.h>
#include <iostream>
#include "const_struct_def.h"

int main(){
	std::vector<std::vector <Queue_element> > temp[N_FLOORS][N_BUTTONS];
	for(std::vector<std::vector <Queue_element> >::iterator it = temp.begin(); it != temp.end(); it++){
		
	}
	Queue_element temp2;
	temp2.active_button = 1;
	temp2.elevator_ID = 3;
	temp[0][1] = temp2;
	std::cout << temp[0][1].active_button << " : " << temp[0][1].elevator_ID << std::endl;


	return 0;
}