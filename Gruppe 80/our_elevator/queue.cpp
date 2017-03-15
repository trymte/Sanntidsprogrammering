#include "queue.h"

//----------------------------------------------------------------------------------------------------
//Constructor and destructor
//----------------------------------------------------------------------------------------------------

Queue::Queue(){
	std::vector<std::vector<Queue_element> > temp = init_twoD_vector();
	this->order_matrix = temp;
}

Queue::~Queue(){
	std::vector<std::vector<Queue_element> >::iterator row;

	for (row = this->order_matrix.begin(); row!=this->order_matrix.end();++row){
		row->erase(row->begin(),row->end());
	}
	this->order_matrix.erase(this->order_matrix.begin(),this->order_matrix.end());
}


//----------------------------------------------------------------------------------------------------
//Private member functions
//----------------------------------------------------------------------------------------------------

void Queue::add_order(std::vector <std::vector <Queue_element> > &order_matrix, Order &new_order, int elevator_ID){
	order_matrix[new_order.floor][new_order.btn].active_button = 1;
	order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
}


unsigned int Queue::calculate_cost(Order order, Status status){
	unsigned int cost = 0;
	switch(status.current_state){
		case MOVING:

			if((order.floor-status.last_floor > 0)){
				if(status.dir == D_Up)
					cost += abs(order.floor - (status.last_floor+1))*10+7;
				else if(status.dir == D_Down)
					cost += abs(order.floor - (status.last_floor-1))*30;

			}

			else if(order.floor-status.last_floor < 0){
				if(status.dir == D_Up)
					cost += abs(order.floor - (status.last_floor+1))*30;
				else if(status.dir == D_Down)
					cost += abs(order.floor - (status.last_floor-1))*10 + 7;
			}
			else{
				cost += abs(order.floor - (status.last_floor+1))*20;
			}
			break;

		case IDLE:
			cost += abs(order.floor-status.floor)*15 + 1;
			break;

		case DOOR_OPEN:
			cost += abs(order.floor-status.floor)*30;
			break;

		default:
			cost += 200;
		}
	return cost;
}


unsigned int Queue::get_lowest_cost_elevator(Order order, std::vector<Status>& status_vector, std::vector<Elevator*> elevators){
	unsigned int temp_cost = 0;
	unsigned int lowest_cost = 10000;
	int elevator_ID = -1;
	Status status_it;
	for(unsigned int i = 0; i<N_ELEVATORS; i++){
		status_it = status_vector[i];
		if (elevators[i]->get_condition()){
			temp_cost = calculate_cost(order,status_it);
			if (temp_cost < lowest_cost){
				lowest_cost = temp_cost;
				elevator_ID = status_it.elevator_ID;
			}
		}
	}
	return elevator_ID;
}


//--------------------------------------------------------------------------------------------------
//Public member functions
//----------------------------------------------------------------------------------------------------


std::vector<std::vector<Queue_element> > Queue::assign_elevators_to_orders(std::vector<Elevator*> elevators, int elevator_ID){

	//Create a status_vector based on the input.
	std::vector<Status> status_vector;
	Status iteration_status;
	for (unsigned int i = 0; i < N_ELEVATORS; i++){		
		status_vector.push_back(elevators[i]->get_status());
	}

	//Create an order_matrix that contains all the orders assigned to an elevator
	std::vector <std::vector <Queue_element> > assigned_order_matrix = init_twoD_vector();
	std::vector <std::vector <Queue_element > > curr_order_matrix = init_twoD_vector();
	assigned_order_matrix = *elevators[elevator_ID]->get_order_matrix_ptr(); 
	Order order_to_be_assigned;
	int assigned_elevator_ID = -1;

	for(unsigned int k = 0; k < N_ELEVATORS; k++){
		curr_order_matrix = *elevators[k]->get_order_matrix_ptr();
		for (unsigned int i=0;i<N_FLOORS;i++){           
			for(unsigned int j=0;j<N_BUTTONS-1;j++){

				//Find elevator with lowest cost and add order to assigned_order_matrix
				if ((curr_order_matrix[i][j].active_button == 1) && (curr_order_matrix[i][j].elevator_ID == -1)){
					order_to_be_assigned.floor = i;
					order_to_be_assigned.btn = (Button)j;
					assigned_elevator_ID = Queue::get_lowest_cost_elevator(order_to_be_assigned,status_vector, elevators);
					Queue::add_order(assigned_order_matrix, order_to_be_assigned, assigned_elevator_ID);
				}
			}
		}
	}
	return assigned_order_matrix;
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


void Queue::add_order(Order new_order, int elevator_ID){
	this->order_matrix[new_order.floor][new_order.btn].active_button = 1;
	this->order_matrix[new_order.floor][new_order.btn].elevator_ID = elevator_ID;
}


void Queue::remove_order(Order order){
	this->order_matrix[order.floor][order.btn].active_button = 0;
	this->order_matrix[order.floor][order.btn].elevator_ID = -1;
}


void Queue::reset_orders(std::vector <std::vector <Queue_element> > &order_matrix, Status status){
	for(unsigned int i = 0; i<N_FLOORS; i++){
		for (unsigned int j = 0; j<N_BUTTONS-1; j++){
			if ((order_matrix[i][j].active_button == 1) && (order_matrix[i][j].elevator_ID == status.elevator_ID)){
				order_matrix[i][j].elevator_ID = -1;
			}
		}
	}
}


void Queue::reset_orders(Status status){
	for(unsigned int i = 0; i<N_FLOORS; i++){
		for (unsigned int j = 0; j<N_BUTTONS-1; j++){
			if ((this->order_matrix[i][j].active_button == 1) && (this->order_matrix[i][j].elevator_ID == status.elevator_ID)){
				this->order_matrix[i][j].elevator_ID = -1;
			}
		}
	}
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
}


void Queue::read_order_matrix_from_file(){
	std::string order_matrix_string;
	std::ifstream file;
	file.open("backup_file.txt");
	std::vector< std::vector< Queue_element > > temp_order_matrix;
	if (file.is_open()){
		getline(file, order_matrix_string);
		temp_order_matrix = string_to_order_matrix(order_matrix_string); 

		//Read only Cab orders from file
		for (unsigned int i = 0; i< N_FLOORS;i++){
			this->order_matrix[i][(int)B_Cab] = temp_order_matrix[i][(int)B_Cab];
		}
	}
}