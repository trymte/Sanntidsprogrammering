#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>


void get_my_ipaddress(std::string &ip){
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
            std::string temp(addressBuffer);
            ip = temp;
        }
    }

    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    
}


int main(){
	std::string ip;
	get_my_ipaddress(ip);
	std::cout << "ipaddress of this computer: " << ip << std::endl;
}