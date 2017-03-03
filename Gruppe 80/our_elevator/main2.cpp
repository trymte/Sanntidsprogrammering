//MORTEN MAIN

#include <iostream>
#include <thread>
#include <unistd.h>

#include "statemachine.h"

pthread_mutex_t lock;



//Kan plasseres i network.cpp
void network_main(Elevator &my_elevator, Queue &my_queue, Network &my_network){
	while(1){}
}

//Skrives mer kompakt? Legge i const_struct_def?
Status init_status;
init_status.dir = D_Stop;
init_status.floor = 0;
init_status.current_state I IDLE;
init_status.out_of_order = 0;
init_status.role = MASTER //Bør være slave til vanlig.


int main(){

	std::mutex my_mutex;

	Queue my_queue;
	Elevator my_elevator(init_status, my_queue.get_order_matrix_ptr());
	Network my_network;


	std::cout << "Initializing threads" << std::endl;
	//std::thread event_manager_thread(event_manager_main(Elevator &my_elevator, Queue &my_queue, Network &my_network));
	std::thread network_thread(network_main(Elevator &my_elevator, Queue &my_queue, Network &my_network));

	//event_manager_thread.join();
	network_thread.join();





/*
	std::cout << "Initializing threads" << std::endl;
	pthread_t state_machine_thread, network_thread;
	int error_thread_1,error_thread_2;
	error_thread_1 = pthread_create(&state_machine_thread, NULL, state_machine_main, NULL);
	if(error_thread_1)
		std::cout << "Error createing state_machine_thread" << std::endl;
	
	error_thread_2 = pthread_create(&network_thread, NULL, network_main, NULL);
	if(error_thread_2)
		std::cout << "Error creating network_thread" << std::endl;

//Joining threads
	std::cout << "Joining threads" << std::endl;
	pthread_join(state_machine_thread, NULL);
	pthread_join(network_thread, NULL);
	*/
}