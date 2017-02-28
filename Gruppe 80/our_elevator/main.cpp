#include <iostream>
#include <thread>
#include <unistd.h>

#include "statemachine.h"

pthread_mutex_t lock;



//Kan plasseres i network.cpp
void network_main(Elevator &my_elevator, Queue &my_queue, Network &my_network){
	while(1){}
}




int main(){

	std::mutex my_mutex;
	Elevator my_elevator;
	Queue my_queue;
	Network my_network;

	std::cout << "Initializing threads" << std::endl;
	std::thread state_machine_thread(state_machine_main(Elevator &my_elevator, Queue &my_queue, Network &my_network));
	std::thread network_thread(network_main(Elevator &my_elevator, Queue &my_queue, Network &my_network));

	state_machine_thread.join();
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