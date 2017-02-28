#pragma once

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string>

#define BUFLEN 512  //Max length of buffer
#define BROADCASTPORT 9000   //The Broadcastport
#define MASTERPORT 20011 //The localport

extern int bsocket, lsocket;

struct code_message{
	char * rip;
	int port;
	char * data;
	int length;
};

void die(char *);

void udp_init(int localport);
int udp_broadcaster(std::string message);
int udp_sender(std::string message, int localport, char* ip);
struct code_message udp_reciever();
struct code_message udp_recieve_broadcast();
void udp_close();

int bytes();
