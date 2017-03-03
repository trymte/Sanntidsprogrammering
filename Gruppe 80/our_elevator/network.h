#pragma once
#include <vector>
#include "Network_files/udp_sendrec.h"
#include "supervisor.h"
#include "elevator.h"
#include "const_struct_def.h"


class Network{
private:
	std::vector<Elevator> elevators;

	Elevator messagestring_to_elevator_object(std::string &messagestring);

	std::string elevator_object_to_messagestring(Elevator &elevator);

public:
	Network();

	std::vector<Elevator> get_elevators(){return elevators;}

	void handle_message(Message message_ID, int elevator_ID);


//------------------------------------------------------------------------
// Kan sløyfe desse funksjonane :
/*
	void slave_send_elevator_information(int elevator_ID);

	void slave_request_order_matrix(int elevator_ID);

	void distribute_order_matrix(int elevator_ID);

	void slave_order_complete(int elevator_ID); //treng me denne?

	void slave_order_incomplete(int elevator_ID);
*/
// ---------------------------------------------------------------------

	void recieve_message_packet();

	void send_message_packet(Message message_ID, int elevator_ID);

};
