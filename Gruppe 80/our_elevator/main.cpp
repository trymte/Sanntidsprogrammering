#include <iostream>
#include <thread>
#include <unistd.h>
#include "eventmanager.h"


int main(){

	//---------------------------------------------------------------------------------------------------
	// Set up connections: Broadcast, local send and recieve + ping
	//---------------------------------------------------------------------------------------------------

	udp_init(MASTERPORT);

	//---------------------------------------------------------------------------------------------------
	// Setting up this elevator, queue and network objects
	//---------------------------------------------------------------------------------------------------

	Status init_status = init_elev_status();
	init_status.ip = get_my_ipaddress();
	int this_elev_id;
	std::cout << "Write in your elevator id: " << std::endl;
	std::cin >> this_elev_id;
	while((this_elev_id > N_ELEVATORS-1) || (this_elev_id < 0)){
		std::cout << "Illegal elevator id, there are only " << N_ELEVATORS << " elevators. Please choose elevator id again" << std::endl;
		std::cin >> this_elev_id;
	}
	init_status.elevator_ID = this_elev_id;
	Queue my_queue;
	Network my_network = Network(init_status, my_queue.get_order_matrix_ptr(), this_elev_id);
	Elevator* my_elevator;
	my_elevator = my_network.get_elevator_ptr(this_elev_id);
    my_elevator->set_order_matrix_ptr(my_queue.get_order_matrix_ptr());

    //---------------------------------------------------------------------------------------------------
    // Setting up threads for the eventmanager and network
    //---------------------------------------------------------------------------------------------------

	std::thread event_manager_thread(event_manager_main,std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));
	std::thread network_send_thread(network_send, std::ref(my_elevator), std::ref(my_network));
	std::thread network_recieve_thread(network_recieve, std::ref(my_elevator), std::ref(my_network));
	std::thread network_ping_thread(network_ping, std::ref(my_elevator), std::ref(my_network));

	event_manager_thread.join();
	network_send_thread.join();
	network_recieve_thread.join();
	network_ping_thread.join();

    return 0;
}