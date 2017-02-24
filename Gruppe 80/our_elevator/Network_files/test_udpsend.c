#include <stdio.h>
#include <unistd.h>
#include "sverresnetwork.h"

void 
udpmessageReceived(const char * ip, int port, char * data, int datalength){

  printf("Received UDP message from %s:%d: '%s'\n",ip,port,data);
  
}

int main(){
//  char * ip = "129.241.10.74";
  char * ip = "129.241.187.161";


  udp_send(ip,20011,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",40);



  return 0;
}

