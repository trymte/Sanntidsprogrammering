#include <stdio.h>
#include <unistd.h>
#include "sverresnetwork.h"

void 
messageReceived(const char * ip, char * data, int datalength){

  printf("Received message from %s: '%s'\n",ip,data);
}

void 
connectionStatus(const char * ip, int status){

  printf("A connection got updated %s: %d\n",ip,status);
}



int main(){

  tcp_init(messageReceived,connectionStatus);


  tcp_openConnection("129.241.187.161",20011);

  tcp_send("129.241.187.161","aaaaaaaaaa",10);

  return 0;
}

