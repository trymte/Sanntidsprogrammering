#pragma once


#include <stdlib.h> //exit(0);
#include <stdio.h>      
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <vector>
#include <iostream>
#include <string>




#define BUFLEN 512  //Max length of buffer
#define BROADCASTPORT 29999   //The Broadcastport
#define BROADCASTIP "129.241.187.255"
#define MASTERPORT 20014 //The localport
#define LOCALHOST "127.0.0.1"
extern int bsocket, lsocket;

struct code_message{
	std::string rip;
	int port;
	std::string data;
	int length;
};

void die(char *);

void udp_init(int localport, int elevator_role);
int udp_broadcaster(std::string message);
int udp_sender(std::string message, int localport, char* ip);
struct code_message udp_reciever();
struct code_message udp_recieve_broadcast();
void udp_close();
void get_my_ipaddress(std::string &ip);
std::string get_my_ipaddress();

int bytes();
