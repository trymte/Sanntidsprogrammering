//#include <iostream>
#include <stdio.h>
#include <pthread.h>

void* state_machine_main(){
	printf("Hello from state_machine\n");
}

void* network_main(){
	printf("Hello from network\n");
}


int main(){
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_t state_machine_thread;
    pthread_create(&state_machine_thread, NULL, statemachine_main, NULL);

    pthread_t network_thread;
    pthread_create(&network_thread, NULL, network_main, NULL);

    pthread_join(state_machine_thread, NULL);
    pthread_join(network_thread, NULL); 
}