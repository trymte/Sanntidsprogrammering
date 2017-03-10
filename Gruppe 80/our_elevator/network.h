#pragma once
#include "timer.h"
#include "supervisor.h"
#include "queue.h"



class Network{
private:
	std::vector<Elevator*> elevators;

	std::string master_ip;

	Elevator messagestring_to_elevator_object(std::string &messagestring);

	std::string elevator_object_to_messagestring(Elevator &elevator);

public:
	Network();

	~Network();

	Network(Status elevator_status, std::vector<std::vector<Queue_element> > *order_matrix_ptr, int elevator_ID);

	std::vector<Elevator*> get_elevators(){return elevators;}

	//std::vector<Elevator>* get_elevators_ptr(){return &elevators;}

	Elevator* get_elevator_ptr(int elevator_ID){return elevators[elevator_ID];}

	std::string get_master_ip(){return master_ip;}

	void handle_message(Message message_ID, int foreign_elevator_ID, int this_elevator_ID);

	void recieve_message_packet(int this_elevator_ID);

	void send_message_packet(Message message_ID, int this_elevator_ID, std::string reciever_ip);

	void set_master_ip(std::string master_ip){this->master_ip = master_ip;}

	bool is_node_responding(int this_elevator_ID, int foreign_elevator_ID);

	void check_responding_elevators(int this_elevator_ID);

	void check_my_role(int this_elevator_ID);


};


void listen_on_network(Elevator* my_elevator, Network &my_network, Queue &my_queue);


