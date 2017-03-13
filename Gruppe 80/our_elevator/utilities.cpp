#include "utilities.h"

std::vector<std::vector<Queue_element> > init_twoD_vector(){
    std::vector<std::vector<Queue_element> > temp;
    Queue_element init_element;
    init_element.active_button = 0;
    init_element.elevator_ID = -1;
    for (unsigned int i=0;i<N_FLOORS;i++){
        std::vector<Queue_element> rowvector;
        for(unsigned int j=0;j<N_BUTTONS;j++){
            rowvector.push_back(init_element);
        }
        temp.push_back(rowvector);
    }   
    return temp;
}


std::vector<std::vector <Queue_element> > string_to_order_matrix(std::string &order_matrix_string){
	std::vector<std::vector <Queue_element> > order_matrix = init_twoD_vector();
	std::stringstream ss2(order_matrix_string);
	int count = 0;
	int temp_floor = 0;
	Queue_element temp_queue_element;
	std::string queue_element_string;
	std::string act_btn;
	std::string elev_id;
	while(std::getline(ss2,queue_element_string, '&')){
		if(count == 3){
			temp_floor +=1;
			count = 0;
		}
		if(queue_element_string.size() == 2){
			act_btn = queue_element_string[0];
			elev_id = queue_element_string[1];
		} else if(queue_element_string.size() == 3){
			act_btn = queue_element_string[0];
			elev_id = queue_element_string.substr(1, 2);
		}
		if(act_btn == "0"){
			temp_queue_element.active_button = false;
		} else{
			temp_queue_element.active_button = true;
		}
		
		temp_queue_element.elevator_ID = atoi(elev_id.c_str());
		order_matrix[temp_floor][count] = temp_queue_element;
		count += 1;
	}
	return order_matrix;
}

std::string order_matrix_to_string(std::vector<std::vector <Queue_element> > *order_matrix_ptr){
	std::stringstream ss;
	std::vector<std::vector <Queue_element> > order_matrix = *order_matrix_ptr;
	for(unsigned int i = 0; i < N_FLOORS; i++){
		for(unsigned int j = 0; j < N_BUTTONS; j++){
			ss << order_matrix[i][j].active_button << order_matrix[i][j].elevator_ID << "&";
		}
	}
	return ss.str();
}

void print_order_matrix(std::vector<std::vector <Queue_element> > *order_matrix_ptr){
	std::cout << "Order matrix: " << std::endl;
	std::vector<std::vector <Queue_element> > ordr = *order_matrix_ptr;
	for(unsigned int i = 0; i < N_FLOORS;i++){
		std::cout << "|  ";
		for(unsigned int j = 0; j < N_BUTTONS; j++){
			Queue_element temp = ordr[i][j];
			std::cout << temp.active_button << " : " << temp.elevator_ID << "   |  "; 
		}
	std::cout << std::endl;
	}

}

Status init_elev_status(){
    return {.ip = "", .dir = D_Stop, .floor = 0, .last_floor = 0, .current_state = IDLE, .elevator_ID = 0, .out_of_order = false, .online = false, .role = SLAVE};
}