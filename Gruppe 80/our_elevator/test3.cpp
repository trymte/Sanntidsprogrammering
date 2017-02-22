#include <iostream>
#include <thread>

pthread_mutex_t lock;
int i = 0;

void* state_machine_main(void*){
	for (int j=0;j<1000000;j++){
		pthread_mutex_lock(&lock);
		i++;
		pthread_mutex_unlock(&lock);
	}
}

void* network_main(void*){
	for (int k=0;k<1000000;k++){
		pthread_mutex_lock(&lock);
		i--;
		pthread_mutex_unlock(&lock);
	}
}


int main(){
//Initializing threads
	std::cout << "Initializing threads" << std::endl;
	pthread_t state_machine_thread, network_thread;
	int error_thread_1,error_thread_2;
	error_thread_1 = pthread_create(&state_machine_thread, NULL, state_machine_main, NULL);
	if(error_thread_1)
		std::cout << "Error createing state_machine_thread" << std::endl;
	
	error_thread_2 = pthread_create(&network_thread, NULL, network_main, NULL);
	if(error_thread_2)
		std::cout << "Error creating network_thread" << std::endl;

	std::cout << "Joining threads" << std::endl;
	pthread_join(state_machine_thread, NULL);
	pthread_join(network_thread, NULL);
}