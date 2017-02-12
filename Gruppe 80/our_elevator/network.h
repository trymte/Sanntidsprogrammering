
#include "queue.h"
#include "supervisor.h"
#include "elevator.h"
#include <string>
#include <iostream>


typedef struct{
	int elevator_ID;
	bool online;
} Elevator_online;

class Network{
private:
	int n_elevators;
	Elevator elevators[n_elevators];
	Elevator_online elevators_online[n_elevators];
	void nw_messagestring_to_object(string message);
public:
	Network(int n_elevators);

	void nw_message_recieve();

	void nw_inform_supervisor(Elevator &elevator);

	void nw_slave_request_order_matrix();

	void nw_distribute_order_matrix(Queue_element &order_matrix_ptr);

	Elevator* nw_get_elevators(){return elevators;}

	void nw_slave_order_complete(Elevator &elevator);

	void nw_slave_order_incomplete(Elevator &elevator);

	bool nw_ping_elevator(Elevator &elevator);

};
