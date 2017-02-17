#include <stdio.h>
#include <unistd.h>
#include "sverresnetwork.h"

void 
udpmessageReceived(const char * ip, int port, char * data, int datalength){

  printf("Received UDP message from %s:%d: '%s'\n",ip,port,data);
  
}

int 
main(){

<<<<<<< HEAD
  udp_broadcast(20011,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",10);
=======
  udp_broadcast(20011,"Hello all\n",12);
>>>>>>> 22356072765439ac24c9684854102485991bf8ee

  return 0;
}

