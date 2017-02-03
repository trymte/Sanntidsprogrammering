#include <stdio.h>
#include <unistd.h>
#include "sverresnetwork.h"

void 
udpmessageReceived(const char * ip, int port, char * data, int datalength){

  printf("Received UDP message from %s:%d: '%s'\n",ip,port,data);
  
}

int 
main(){

  udp_broadcast(20011,"Hello all\n",12);

  return 0;
}

