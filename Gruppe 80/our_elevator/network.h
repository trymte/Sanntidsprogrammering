#pragma once
#include "supervisor.h"
#include "queue.h"
#include <mutex>

class Network{
private:
	std::vector<Elevator*> elevators;

	std::string master_ip;

	int master_ID;

	Elevator messagestring_to_elevator_object(std::string &messagestring);

	std::string elevator_object_to_messagestring(Elevator &elevator);

public:
	Network();

	~Network();

	Network(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix_ptr, int elevator_ID);

//----------------------------------------------------------------------------------------------------------------------
//		Network get functions
//----------------------------------------------------------------------------------------------------------------------

	std::vector<Elevator*> get_elevators(){return elevators;}

	Elevator* get_elevator_ptr(int elevator_ID){return elevators[elevator_ID];}

	std::string get_master_ip(){return master_ip;}

//----------------------------------------------------------------------------------------------------------------------
//		Network set functions
//----------------------------------------------------------------------------------------------------------------------

	void set_master_ip(std::string master_ip){this->master_ip = master_ip;}

	void handle_message(Message message_ID, int this_elevator_ID, int foreign_elevator_ID);

	void recieve_message_packet(int this_elevator_ID);

	void recieve_handshake_message(int this_elevator_ID);

	void send_message_packet(Message message_ID, int this_elevator_ID, std::string reciever_ip);

	bool is_node_responding(int this_elevator_ID, int foreign_elevator_ID);

	void check_responding_elevators(int this_elevator_ID);

	void check_my_role(int this_elevator_ID);
};


//----------------------------------------------------------------------------------------------------------------------
//		Network thread functions
//----------------------------------------------------------------------------------------------------------------------

void network_send(Elevator* my_elevator, Network &my_network);

void network_recieve(Elevator* my_elevator, Network &my_network);

void network_ping(Elevator* my_elevator, Network &my_network);