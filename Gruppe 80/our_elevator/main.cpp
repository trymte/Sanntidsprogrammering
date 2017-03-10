
#include <iostream>
#include <thread>
#include <unistd.h>

#include "eventmanager.h"


int main(){
	Status init_status;
	init_status.ip = get_my_ipaddress();
	std::cout << "My ip address: " << init_status.ip << std::endl;
	init_status.out_of_order = false;
	std::cout << "Write in your role: " << std::endl;
	int role;
	std::cin >> role;
	init_status.role = static_cast<Role>(role);

	udp_init(MASTERPORT, static_cast<int>(init_status.role));
	

	int this_elev_id;
	std::cout << "Write in your elevator id: " << std::endl;
	std::cin >> this_elev_id; 
	Queue my_queue;
	Network my_network = Network(init_status, my_queue.get_order_matrix_ptr(), this_elev_id);
	Elevator* my_elevator;
	my_elevator = my_network.get_elevator_ptr(this_elev_id);
    my_elevator->set_elevator_order_matrix_ptr(my_queue.get_order_matrix_ptr());
    usleep(5000000);
    switch(init_status.role){
		case MASTER:
			my_network.send_message_packet(MASTER_IP_INIT, this_elev_id);
			break;
		case SLAVE:
			my_network.recieve_message_packet(my_elevator->get_elevator_ID());
			break;
	}
    
	std::thread event_manager_thread(event_manager_main,std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));
	std::thread network_thread(listen_on_network, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));

	event_manager_thread.join();
	network_thread.join();

    return 0;
}