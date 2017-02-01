/*


    What is concurrency? 
    What is parallelism? 
    What's the difference?
		Concurrency: Starte programmer samtidig, hvor de overlapper hverandre, men ikke nødvendigvis kjører samtidig.
		Parallelism: Kjøre programmer samtidig, ie. på en flerkjernet prosessor

    Why have machines become increasingly multicore in the past decade?
		Muligheten for å parallelisere oppgaver, øker hastigheten.

    What kinds of problems motivates the need for concurrent execution? (Or phrased differently: What problems do concurrency help in solving?)
		Hvis du kjører programmer som krever at flere oppgaver blir kjørt samtidig. Spesielt hvis du har single-core prosessor, men selv med 
		multicore processor kan dette forbedre ytelsen.

    Does creating concurrent programs make the programmer's life easier? Harder? Maybe both? (Come back to this after you have worked on part 4 of this 
    exercise)
		Kanskje litt vanskeligere... 

    What are the differences between processes, threads, green threads, and coroutines?
		Processes: Kjøres fra operativsystemet, har eget minne
		Threads: Kjøres i en bestemt prosess, kan ha delt minne med andre tråder
		Green threads: En type cooperativ thread. Kjøres fra applikasjoner eller virtuelle maskiner.
		Coroutines: Rutine som kaller på andre rutiner mens den kjører. 


    Which one of these do pthread_create() (C/POSIX), threading.Thread() (Python), go (Go) create?
		


    How does pythons Global Interpreter Lock (GIL) influence the way a python Thread behaves?
    	Kjører en tråd av gangen på en kjerne.


    With this in mind: What is the workaround for the GIL (Hint: it's another module)?


    What does func GOMAXPROCS(n int) int change?
    	Forandre hvor mange tråder som tillates å kjøres samtidig. 
*/

#include <pthread.h>
#include <stdio.h>

int i = 0;

void* thread_1_function(){
	int j;
	
	for (j=0;j<1000000;j++){
		i++;
		printf("Run thread 1\n");
	}
	return NULL;
}

void* thread_2_function(){
	int k;
	
	for (k=0;k<1000000;k++){
		i--;
		printf("Run thread 2\n");
	}
	return NULL;
}


int main(){
    pthread_t thread_1;
    pthread_create(&thread_1, NULL, thread_1_function, NULL);

    pthread_t thread_2;
    pthread_create(&thread_2, NULL, thread_2_function, NULL);
    printf("Threads created\n");

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("%d\n",i);
}