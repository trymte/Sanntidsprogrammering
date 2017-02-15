

#include "queue.h"
#include "supervisor.h"
#include "elevator.h"
#include "sverres_network.h"
#include <string>
#include <iostream>
#include <stringstream>


typedef struct{
	int elevator_ID;
	bool online;
} Elevator_online;

class Network{
private:
	int n_elevators;
	Elevator elevators[n_elevators];
	Elevator_online elevators_online[n_elevators];
	void nw_messagestring_to_elevator_object(string &message);
public:
	Network();
	Network(int n_elevators);

	Elevator* nw_get_elevators(){return elevators;}

	void nw_message_recieve();

	void nw_inform_supervisor(Elevator &elevator);

	void nw_slave_request_order_matrix();

	void nw_distribute_order_matrix(Queue_element &order_matrix_ptr);

	void nw_slave_order_complete(Elevator &elevator);

	void nw_slave_order_incomplete(Elevator &elevator);

	bool nw_ping_elevator(Elevator &elevator);

};
