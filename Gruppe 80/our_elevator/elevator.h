#include <queue.h>

class Elevator friend Queue{
private:
	int dir;
	int floor;
	int elevatorID;
	bool out_of_order;
	queue_element* order_matrix_ptr;
public:
	Elevator(int dir, int floor, int elevatorID, bool out_of_order)
	int get_floor();
	int get_dir();
	int get_elev_id();
	bool get_elev_status();


};

void assign_elevators_to_orders(Elevator &elevators);