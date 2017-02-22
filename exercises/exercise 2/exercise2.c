/*

    An atomic operation?
		An instantaneous operation, indivisible, irreducible, 
		must happen or not happen at all. An atomic operation can read and write in the same bus operation/cycle?
		No other threads can observe the modification half-complete. 
    A semaphore?
     A variable that controls access to a common resource (flag) by telling if the resource is available?
    
    A mutex?
     A concept that only lets one thread access a section of code/a variable at a time, blocking out other threads.

    A critical section?
		Where a thread accesses a shared resource. 

*/

#include <pthread.h>
#include <stdio.h>

int i = 0;
pthread_mutex_t lock;


void* thread_1_function(){
	int j;
	for (j=0;j<1000000;j++){
		pthread_mutex_lock(&lock);
		i++;
		pthread_mutex_unlock(&lock);
	}
	

	return NULL;
}

void* thread_2_function(){
	int k;
	for (k=0;k<1000000;k++){
		pthread_mutex_lock(&lock);
		i--;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}


int main(){
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }


    pthread_t thread_1;
    pthread_create(&thread_1, NULL, thread_1_function, NULL);

    pthread_t thread_2;
    pthread_create(&thread_2, NULL, thread_2_function, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("%d\n",i);
}