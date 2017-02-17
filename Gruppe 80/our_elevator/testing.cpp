#include "queue.h"
#include "queue.cpp"
#include "elevator.cpp"

using namespace std;

int main(){
	Status status;
	status.dir = D_Down;
	status.floor = 2;
	status.elevator_ID = 1;
	status.out_of_order = 0;


	Elevator a(status);
	print_status(a.get_elevator_status());
	Queue::queue_print_order_matrix(a.get_order_matrix_ptr());

	std::vector<Elevator> elevators;
	elevators.push_back (a);
	
/*
	Queue::queue_assign_elevators_to_orders(elevators);
*/
}
