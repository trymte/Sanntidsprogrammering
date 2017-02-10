

Elevator::Elevator(Status elevator_status): 
{
	this->elevator_status = elevator_status;
	//order_matrix_ptr = Queu::queue_get_order_matrix();
	order_matrix_ptr = queue1.queue_get_order_matrix();
}

Elevator::~Elevator(){
	if(order_matrix_ptr != NULL){
		for(int i = 0; i < N_FLOORS; i++){
			delete [] order_matrix_ptr[i];
		delete [] order_matrix_ptr;
		}
	}
	
}

