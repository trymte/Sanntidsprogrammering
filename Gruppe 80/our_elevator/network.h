#pragma once

#include "queue.h"
#include "supervisor.h"
#include "elevator.h"
#include "Network_files/sverresnetwork.h"
#include "const_struct_def.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


typedef struct{
	int elevator_ID;
	bool online;
} Elevator_online;

class Network{
private:

	std::vector<Elevator> elevators; //Tror elevators må være vector. N_ELEVATORS from const_struct_def.h

	std::vector<Elevator_online> elevators_online;

	void nw_messagestring_to_elevator_object(std::string &message);

	void nw_elevator_object_to_messagestring(Elevator &elevator);
public:
	Network();
	
	Network(int n_elevators);

	std::vector<Elevator> nw_get_elevators(){return elevators;}

	void nw_message_recieve();

	void nw_inform_supervisor(Elevator &elevator);

	void nw_slave_request_order_matrix();

	void nw_distribute_order_matrix(std::vector<std::vector<Queue_element> > *order_matrix_ptr);

	void nw_slave_order_complete(Elevator &elevator);

	void nw_slave_order_incomplete(Elevator &elevator);

	bool nw_ping_elevator(Elevator &elevator);

};
