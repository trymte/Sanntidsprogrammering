#include "queue.h"





//--------------------------------------------------------------------------------------------------
//Constructor and destructor
//----------------------------------------------------------------------------------------------------
Queue::Queue(){
	std::vector<std::vector<Queue_element> > temp = twoD_vector_init();
	this->order_matrix = temp;
}

Queue::~Queue(){
	std::vector<std::vector<Queue_element> >::iterator row;

	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		row->erase(row->begin(),row->end());
	}
	this->order_matrix.erase(this->order_matrix.begin(),this->order_matrix.end());
}


//--------------------------------------------------------------------------------------------------
//Private member functions
//----------------------------------------------------------------------------------------------------

//Her burde calculate_cost ligge
//Fikk problemer med å kalle privat static funksjon fra assign_elevator_to_order, prøve igjen senere...


//--------------------------------------------------------------------------------------------------
//Public member functions
//----------------------------------------------------------------------------------------------------


unsigned int Queue::calculate_cost(Order order, Status status){
	unsigned int cost = 0;
	switch(status.current_state){
		case MOVING:

			if((order.floor-status.floor >= 0) && (status.dir == D_Up))
				cost += abs(order.floor - status.floor)*10;

			else if((order.floor-status.floor < 0) && (status.dir == D_Down))
				cost += abs(order.floor - status.floor)*10;

			else
				cost += 50;

			break;

		case IDLE:
			cost += abs(order.floor-status.floor)*15;
			break;

		case DOOR_OPEN:
			cost += abs(order.floor-status.floor)*30;
			break;

		default:
			cost += 200;
		}

	return cost;
}


unsigned int Queue::get_lowest_cost_elevator(Order order, std::vector<Status>& status_vector){
	unsigned int temp_cost = 0;
	unsigned int lowest_cost = 10000;
	int elevator_ID = -1;
	Status status_it;

	for(std::vector<Status>::iterator it = status_vector.begin(); it != status_vector.end();++it){
		status_it = *it;
		if (status_it.out_of_order != 1){ 
			temp_cost = calculate_cost(order,status_it);
			if (temp_cost < lowest_cost){
				lowest_cost = temp_cost;
				elevator_ID = status_it.elevator_ID;
			}

		}
	}
	return elevator_ID;
}


std::vector<std::vector<Queue_element> > Queue::merge_order_matrices(std::vector <std::vector <Queue_element> > &order_matrix_1,std::vector <std::vector <Queue_element> > &order_matrix_2){
	if ((order_matrix_1.size() != order_matrix_2.size())||(order_matrix_1[0].size() != order_matrix_2[0].size())){
		std::cout << "Dimensions disagree in queue_to_be_merged" << std::endl;
		return order_matrix_1;
	}

	int rows = order_matrix_1.size();
	int cols = order_matrix_1[0].size();

	for (int i = 0;i<rows;i++){
		for (int j=0;j<cols;j++){
			if ((order_matrix_1[i][j].elevator_ID == -1) && (order_matrix_2[i][j].elevator_ID != -1)){
				order_matrix_1[i][j].active_button = order_matrix_2[i][j].active_button;
				order_matrix_1[i][j].elevator_ID = order_matrix_2[i][j].elevator_ID;
			}
		}
	}
	return order_matrix_1;
}


void Queue::merge_order_matrices(Queue &queue_to_be_merged){
	if ((this->order_matrix.size() != queue_to_be_merged.order_matrix.size())||(this->order_matrix[0].size() != queue_to_be_merged.order_matrix[0].size())){
		std::cout << "Dimensions disagree in queue_to_be_merged" << std::endl;
		return;
	}

	int rows = this->order_matrix.size();
	int cols = this->order_matrix[0].size();

	for (int i = 0;i<rows;i++){
		for (int j=0;j<cols;j++){
			if ((this->order_matrix[i][j].elevator_ID == -1) && (queue_to_be_merged.order_matrix[i][j].elevator_ID != -1)){
				this->order_matrix[i][j].active_button = queue_to_be_merged.order_matrix[i][j].active_button;
				this->order_matrix[i][j].elevator_ID = queue_to_be_merged.order_matrix[i][j].elevator_ID;
			}
		}
	}
}




void Queue::add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID){
	if (new_order.floor > N_FLOORS){
		std::cout << "Floor in new_order doesn't match number of floors in system" << std::endl;
		return;
	}
	if (new_order.btn > N_BUTTONS){
		std::cout << "Button in new_order doesn't match number of buttons in system, " << new_order.btn << " > " << N_BUTTONS <<  std::endl;
		return;
	}

	if ((order_matrix.size() < new_order.floor)||(order_matrix[0].size() < new_order.btn)){
		std::cout << "Dimensions disagree in queue_add_order" << std::endl;
		return;
	}

	order_matrix[new_order.floor][new_order.btn].active_button = 1;
	order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
}

void Queue::add_order(Order new_order, int elevator_ID){
	if (new_order.floor > N_FLOORS){
		std::cout << "Floor in new_order doesn't match number of floors in system" << std::endl;
		return ;
	}
	if (new_order.btn > N_BUTTONS){
		std::cout << "Button in new_order doesn't match number of buttons in system" << std::endl;
		return ;
	}
	this->order_matrix[new_order.floor][new_order.btn].active_button = 1;
	this->order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
}


void Queue::remove_order(Order order){
	this->order_matrix[order.floor][order.btn].active_button = 0;
	this->order_matrix[order.floor][order.btn].elevator_ID = -1;
}

void Queue::remove_order(std::vector <std::vector <Queue_element> > &order_matrix,Order order){
	if ((order_matrix.size() < order.floor)||(order_matrix[0].size() < order.btn)){
		std::cout << "Dimensions disagree in queue_remove_order" << std::endl;
	}
	else{
		order_matrix[order.floor][order.btn].active_button = 0;
		order_matrix[order.floor][order.btn].elevator_ID = -1;
	}
}


std::vector<std::vector<Queue_element> > Queue::assign_elevators_to_orders(std::vector<Elevator> &elevators){

	if (elevators.size() == 0){
		std::cout << "Cant assign empty elevators to orders in queue_assign_elevators_to_orders" << std::endl;
		std::vector<std::vector<Queue_element> > empty_order_matrix;
		return empty_order_matrix;
	}

	//Create a status_vector based on the input.
	std::vector<Status> status_vector;
	std::vector<Elevator>::iterator elevator_it;
	Status iteration_status;
	for (elevator_it = elevators.begin();elevator_it != elevators.end();++elevator_it){		
		iteration_status = elevator_it->get_elevator_status();
		status_vector.push_back(iteration_status);
	}

	//Create an order_matrix that contains all the orders assigned to an elevator
	std::vector <std::vector <Queue_element> > assigned_order_matrix;
	std::vector <std::vector <Queue_element > > curr_order_matrix;
	assigned_order_matrix = twoD_vector_init();
	Order order_to_be_assigned;
	int assigned_elevator = -1;

	for(elevator_it = elevators.begin();elevator_it != elevators.end();++elevator_it){
		curr_order_matrix = *elevator_it->get_order_matrix_ptr();
		for (unsigned int i=0;i<N_FLOORS;i++){           //la til unsigned foran int pga uendelig mange warnings i kompilering - trym
			for(unsigned int j=0;j<N_BUTTONS;j++){
				
				//If an order in an order_matrix in elevators is not found in assigned_order_matrix, add it.
				if ((assigned_order_matrix[i][i].active_button == 0)&&(curr_order_matrix[i][j].active_button == 1)){
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = (Button)j;
					Queue::add_order(assigned_order_matrix,order_to_be_assigned,curr_order_matrix[i][j].elevator_ID);
				}


				//Find elevator with lowest cost and add order to assigned_order_matrix
				if ((curr_order_matrix[i][j].active_button == 1) && (curr_order_matrix[i][j].elevator_ID == -1)){
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = (Button)j;
					assigned_elevator = Queue::get_lowest_cost_elevator(order_to_be_assigned,status_vector);
					Queue::add_order(assigned_order_matrix, order_to_be_assigned,assigned_elevator);
				}
			}
		}
	}

	return assigned_order_matrix;
}

void Queue::reset_orders(std::vector <std::vector <Queue_element> > &order_matrix, Status status){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	for (row = order_matrix.begin(); row!=order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			if ((col->active_button == 1)&&(col->elevator_ID == status.elevator_ID))
				col->elevator_ID = -1;
		}
	}
}


void Queue::reset_orders(Status status){
	std::vector<std::vector<Queue_element> >::iterator row;
	std::vector<Queue_element>::iterator col;

	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		for (col = row->begin(); col != row->end(); ++col){
			if ((col->active_button == 1)&&(col->elevator_ID == status.elevator_ID))
				col->elevator_ID = -1;
		}
	}
}



Order Queue::get_next_order(int elevator_ID){
	Order next_order;
	next_order.floor = 0;
	next_order.btn = B_HallDown;
	next_order.active_order = 0;


	for (unsigned int floors = 0; floors<N_FLOORS;floors++){
		for (unsigned int btn = 0;btn<N_BUTTONS;btn++){
			if ((this->order_matrix[floors][btn].active_button == 1)&&(this->order_matrix[floors][btn].elevator_ID == elevator_ID)){
				next_order.floor = floors;
				next_order.active_order = 1;
				next_order.btn = (Button)btn;
				return next_order;
			}
		}
	}
	return next_order;	
}


void Queue::write_order_matrix_to_file(){
	std::ofstream file;
	file.open("backup_file.txt");
	
	if (file.is_open()){

		for (unsigned int i=0;i<N_FLOORS;i++){ 
			for (unsigned int j=0;j<N_BUTTONS;j++){
				file << this->order_matrix[i][j].active_button << this->order_matrix[i][j].elevator_ID << "&";
			}
		}
		file.close();
	}
	else
		std::cout << "Unable to open file at queue_write_order_matrix_to_file" << std::endl; //la til _to_file her for økt lesbarhet :) -trym, tilsvarande i funksjonen under her 
}


void Queue::read_order_matrix_from_file(){
	std::string line;
	std::string result;
	std::ifstream file;
	file.open("backup_file.txt");
	if (file.is_open()){
			while(getline(file,line,':')){
				result += line;
			}

			this->order_matrix = string_to_order_matrix(result); 
	}
	else
		std::cout << "Unable to open file at queue_read_order_matrix_from_file" << std::endl;
}


