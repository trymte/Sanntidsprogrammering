
//NB!!! Exists in elevator_io_types.h, may therefore be deleted! 
typedef enum { 
    B_HallUp,
    B_HallDown,
    B_Cab
} Button;

typedef enum { 
    D_Down  = -1,
    D_Stop  = 0,
    D_Up    = 1
} Dirn;
//NB!!! Exists in elevator_io_types.h, may therefore be deleted! 

//Move to elevator.h
class Elevator{};

struct Queue_element{
	bool active_button;
	unsigned int elevator_ID;
};

struct Order{
	unsigned int floor;
	Button btn;
};

struct Status{
	Dirn dir;
	unsigned int floor;
	unsigned int elevator_ID;
	bool out_of_order;
};



class Queue{
private:
	unsigned int n_buttons;
	unsigned int n_floors;

	Queue_element **order_matrix;
	unsigned int queue_calculate_cost(Order order, Status &status_array);
	void queue_write_order_matrix();
	void queue_read_order_matrix();

public:
	Queue::Queue(unsigned int n_buttons, unsigned int n_floors);
	void Queue::queue_add_order(Order new_order,unsigned int elevator_ID);
	void Queue::queue_remove_order(Elevator &elevator);
	Queue_element Queue::queue_get_order_matrix();
	void Queue::queue_assign_elevators_to_orders(Elevator &elevators);
	void Queue::queue_merge_order_matrices(Queue_element* new_order_matrix);
	void Queue::queue_reset_orders(Elevator &elevator);
}