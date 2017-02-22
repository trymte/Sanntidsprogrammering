#pragma once

#include "Network_files/sverresnetwork.h"
#include "supervisor.h"
#include "elevator.h"
#include "const_struct_def.h"

typedef struct{
	int elevator_ID;
	bool online;
} Elevator_online;

class Network{
private:
	std::vector<Elevator> elevators;

	std::vector<Elevator_online> elevators_online;

	Elevator messagestring_to_elevator_object(std::string &messagestring);

	std::string elevator_object_to_messagestring(Elevator &elevator);

public:
	Network();

	std::vector<Elevator> get_elevators(){return elevators;}

	void message_recieve(std::string message_ID, int elevator_ID);

	void inform_supervisor(Elevator &elevator);

	void slave_request_order_matrix();

	void distribute_order_matrix(std::vector<std::vector<Queue_element> > &order_matrix);

	void slave_order_complete(Elevator &elevator);

	void slave_order_incomplete(Elevator &elevator);

	bool ping_elevator(Elevator &elevator);

};
