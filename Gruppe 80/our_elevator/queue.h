#ifndef QUEUE_H
#define QUEUE_H

//NB!!! Exists in elevator_io_types.h, may therefore be deleted! 
typedef enum { 
    B_HallUp = 0,
    B_HallDown = 1,
    B_Cab = 2
} Button;

typedef enum { 
    D_Down  = -1, //1,
    D_Stop  = 0, //0,
    D_Up    = 1 //1
} Dirn;
//NB!!! Exists in elevator_io_types.h, may therefore be deleted! Nye verdier gjør det kompatibelt med queue_matrix







struct Queue_element{
	bool active_button;
	int elevator_ID;
};

struct Order{
	unsigned int floor;
	Button btn;
};

struct Status{
	Dirn dir;
	unsigned int floor;
	int elevator_ID;
	bool out_of_order;
};



class Queue{
private:
	unsigned int n_buttons;
	unsigned int n_floors;
	Queue_element order_matrix[n_floors][n_buttons];
	

	

public:
	//Supposed to be private:
	unsigned int queue_calculate_cost(Order order, std::vector<Status>& status_vector);
	void queue_write_order_matrix();
	void queue_read_order_matrix();
	//


	

	Queue(unsigned int n_floors,unsigned int n_buttons);
	void queue_add_order(Order new_order,int elevator_ID);
	Queue_element** queue_get_order_matrix();	
	void queue_merge_order_matrices(Queue queue_with_new_order_matrix);
	void queue_print_order_matrix();
	void assign_elevators_to_orders(Elevator &elevators);

	void queue_remove_order(Status status);
	void queue_reset_orders(Status status);

};

#endif