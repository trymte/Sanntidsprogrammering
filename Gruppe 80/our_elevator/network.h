#pragma once

#include "Network_files/udp_sendrec.h"
#include "supervisor.h"
#include "elevator.h"
#include "const_struct_def.h"

typedef struct{
	char* ip;
	int elevator_ID;
	bool online;
} Elevator_online;
//integrere elevator online i out_of_order variabelen til kvar heis?
//Kan funke det. Så i stedet for en bool "out_of_order", så har vi en struct "condition" som tar for seg online og out_of_order? -Morten
class Network{
private:
	std::vector<Elevator> elevators;

	std::vector<Elevator_online> elevators_online;

	Elevator messagestring_to_elevator_object(std::string &messagestring);

	std::string elevator_object_to_messagestring(Elevator &elevator);

public:
	Network();

	std::vector<Elevator> get_elevators(){return elevators;}

	void handle_message(Message message_ID, int elevator_ID);

	//void inform_supervisor(Elevator elevator); Trenger vi? 

//------------------------------------------------------------------------
// Kan sløyfe desse funksjonane :
	void slave_send_elevator_information(int elevator_ID);

	void slave_request_order_matrix(int elevator_ID);

	void distribute_order_matrix(int elevator_ID);

	void slave_order_complete(int elevator_ID); //treng me denne?

	void slave_order_incomplete(int elevator_ID);

// ---------------------------------------------------------------------

	void recieve_message_packet();

	void send_message_packet(Message message_ID, int elevator_ID);

};
