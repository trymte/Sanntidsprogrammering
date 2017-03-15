#pragma once

#include <stdlib.h>
#include <stdio.h>      
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <string>

#define BUFLEN 512  					//  Max length of buffer
#define BROADCASTPORT 29999  		    //  The broadcastport used for broadcasting order matrix from master to slaves
#define MASTERPORT 22356 				//  The port used for sending direct messages from slave to master
#define PINGPORT 25000					//  The port used for handshakes between every elevator (master and slaves)
#define BROADCASTIP "129.241.187.255"

struct code_message{
	std::string data;
	bool responding;
};

void die(char *);

void get_my_ipaddress(std::string &ip);

std::string get_my_ipaddress();

void udp_init(int localport);

void udp_broadcaster(std::string message);

void udp_sender(std::string message, int localport, char* reciever_ip);

void udp_handshake_sender(std::string message, int localPort, char * reciever_ip);

struct code_message udp_reciever();

struct code_message udp_handshake_reciever();

struct code_message udp_recieve_broadcast();

void udp_close();


