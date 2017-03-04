//TEST MAIN FOR Å PRØVE Å SENDE MELDING OVER NETTVERK
#include "const_struct_def.h"
#include "queue.h"
#include "network.h"
#include <stdio.h>
#include <thread>
#include <unistd.h>



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



int main(){
	udp_init(MASTERPORT);
	std::cout << "Hello, welcome to network testing " << std::endl;
	Status init_status;
	init_status.ip = get_my_ipaddress();
	init_status.dir = D_Up;
	init_status.floor = 3;
	init_status.current_state = DOOR_OPEN;
	init_status.out_of_order = true;
	init_status.role = SLAVE;
	Queue my_queue;
	Elevator * my_elevator;
	Network my_network = Network(init_status, my_queue.get_order_matrix_ptr());

	int this_elev_id;
	std::cout << "Write in elevator id: " << std::endl;
	std::cin >> this_elev_id; 
    my_elevator = my_network.get_elevator_ptr(this_elev_id);


	//std::thread event_manager_thread(event_manager_main(std::ref(my_elevator), std::ref(my_queue), std::ref(my_network)));
	std::thread network_thread(network_main, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));

	//event_manager_thread.join();
	network_thread.join();
    return 0;
}