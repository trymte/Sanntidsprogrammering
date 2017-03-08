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
	std::mutex my_mutex;

	Status init_status;
	init_status.ip = get_my_ipaddress();
	std::cout << "My ip address: " << init_status.ip << std::endl;
	init_status.dir = D_Up;
	init_status.floor = 3;
	init_status.current_state = IDLE;
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
	Elevator* my_elevator;
	Network my_network = Network(init_status, my_queue.get_order_matrix_ptr(), this_elev_id);
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
    
	std::thread event_manager_thread(event_manager_main,std::ref(my_elevator), std::ref(my_queue), std::ref(my_network));
	std::thread network_thread(listen_on_network, std::ref(my_elevator), std::ref(my_network), std::ref(my_queue));

	event_manager_thread.join();
	network_thread.join();

    return 0;
}