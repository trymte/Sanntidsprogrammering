//TEST MAIN FOR Å PRØVE Å SENDE MELDING OVER NETTVERK
#include "network.h"
#include <stdio.h>
#include <thread>
#include <unistd.h>


/*
void network_send(Elevator* my_elevator, Network &my_network, Queue &my_queue){
	while(1){
		switch(my_elevator->get_elevator_role()){
			case MASTER:
				usleep(250000);
				std::cout << "master send via broadcast" << std::endl;
				my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_elevator_ID());
				break;
			case SLAVE:
				usleep(250000);
				std::cout << "slave Send via send" << std::endl;
				my_network.send_message_packet(SLAVE_REQUEST_ORDER_MATRIX, my_elevator->get_elevator_ID());
				
				break;
		}
	}
}

void network_listen(Elevator* my_elevator, Network &my_network, Queue& my_queue){
	while(1){
		switch(my_elevator->get_elevator_role()){
			case MASTER:
				usleep(250000);
				std::cout << "master recieve via broadcast" << std::endl;
				my_network.master_recieve_message_packet();
			case SLAVE:
				usleep(250000);
				std::cout << "slave Recieve via send" << std::endl;
				my_network.slave_recieve_message_packet();
				break;
		}
	}
}
*/

int main(){
	
	Status init_status;
	init_status.ip = get_my_ipaddress();
	std::cout << "My ip address: " << init_status.ip << std::endl;
	init_status.dir = D_Up;
	init_status.floor = 3;
	init_status.current_state = IDLE;
	init_status.out_of_order = false;
	init_status.role = SLAVE;
	std::cout << "I am: " << init_status.role << std::endl;
	

	udp_init(MASTERPORT, static_cast<int>(init_status.role));
	Queue my_queue;
	Elevator * my_elevator;
	Network my_network = Network(init_status, my_queue.get_order_matrix_ptr());

	int this_elev_id;
	std::cout << "Write in elevator id: " << std::endl;
	std::cin >> this_elev_id; 
    my_elevator = my_network.get_elevator_ptr(this_elev_id);
    usleep(5000000);

	//std::thread event_manager_thread(event_manager_main(std::ref(my_elevator), std::ref(my_queue), std::ref(my_network)));
	//std::thread network_listen_thread(network_listen, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));
	//std::thread network_send_thread(network_send, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));
	std::thread network_thread(network_main, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));


	//event_manager_thread.join();
	//network_listen_thread.join();
	//network_send_thread.join();
	network_thread.join();
    return 0;
}