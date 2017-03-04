//MORTEN MAIN - har lagt inn litt diverse, bruke denne som hovedmain? -trym

#include <iostream>
#include <thread>
#include <unistd.h>

#include "eventmanager.h"

pthread_mutex_t lock;



/*
void network_main(Elevator* my_elevator, Network &my_network, Queue &my_queue){
	while(1){
		switch(my_elevator->get_elevator_role()){
			case MASTER:
				std::cout << "hello1 master" << std::endl;
				usleep(250000);
				my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_elevator_ID());
				std::cout << "hello2 master" << std::endl;
				my_network.master_recieve_message_packet();
				break;
			case SLAVE:

				usleep(250000);
				std::cout << "Send via broadcast" << std::endl;
				my_network.send_message_packet(SLAVE_REQUEST_ORDER_MATRIX, my_elevator->get_elevator_ID());
				std::cout << "Recieve via broadcast" << std::endl;
				my_network.slave_recieve_message_packet();
				break;
		}
	}
}
*/




int main(){

	Status init_status;
	init_status.dir = D_Stop;
	init_status.floor = 0;
	init_status.current_state I IDLE;
	init_status.out_of_order = 0;
	init_status.role = MASTER;
	std::mutex my_mutex;

	Queue my_queue;
	Elevator * my_elevator;
	Network my_network = Network(init_status, my_queue.get_order_matrix_ptr());

	int this_elev_id;
	std::cout << "Write in elevator id: " << std::endl;
	std::cin >> this_elev_id; 
    my_elevator = my_network.get_elevator_ptr(this_elev_id);


	std::thread event_manager_thread(event_manager_main(std::ref(my_elevator), std::ref(my_queue), std::ref(my_network)));
	//std::thread network_thread(network_main, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));

	event_manager_thread.join();
	//network_thread.join();





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