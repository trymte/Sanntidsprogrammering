//TEST MAIN FOR Å PRØVE Å SENDE MELDING OVER NETTVERK
#include "const_struct_def.h"
#include "network.h"
#include "elevator.h"
#include "queue.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <unistd.h>


Status init_status;
init_status.dir = D_Stop;
init_status.floor = 0;
init_status.current_state = IDLE;
init_status.out_of_order = 0;
init_status.role = SLAVE;

Queue my_queue;
Elevator * my_elevator;
Network my_network = Network(init_status, my_queue.get_order_matrix_ptr());

void network_main(){
	while(1){
		switch(my_elevator->get_elevator_role()){
			case MASTER:
				my_network.send_message_packet(MASTER_DISTRIBUTE_ORDER_MATRIX, my_elevator->get_elevator_ID());
				my_network.master_recieve_message_packet();
				break;
			case SLAVE:
				my_network.send_message_packet(SLAVE_REQUEST_ORDER_MATRIX, my_elevator->get_elevator_ID());
				my_network.slave_recieve_message_packet();
				break;
		}
	}
}



int main(){
	
	
	std::cout << "Initializing elev " << std::endl;
	int this_elev_id;
	std::cout << "Write in elevator id: " << std::endl;
	std::cin >> this_elev_id;
    
    my_elevator = my_network.get_elevator_ptr(this_elev_id);

	std::cout << "Initializing threads" << std::endl;
	//std::thread event_manager_thread(event_manager_main(Elevator &my_elevator, Queue &my_queue, Network &my_network));
	std::thread network_thread(network_main);

	//event_manager_thread.join();
	network_thread.join();
    return 0;
}