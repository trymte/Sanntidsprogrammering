#include "udp_sendrec.h"

int bsocket, lsocket, psocket;

void die(char * s)
{
    perror(s);
    udp_close();
    exit(1);
}

void get_my_ipaddress(std::string &ip){
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check if it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN); 
            std::string temp(addressBuffer);
            ip = temp;
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}

std::string get_my_ipaddress(){
    std::string ip;
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
            std::string temp(addressBuffer);
            ip = temp;
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    
    return ip;
}


void udp_init(int localPort){
    struct sockaddr_in laddr, baddr, paddr;
    
    //_------------------------------------------------------------------------
    // Broadcast connection
    //_------------------------------------------------------------------------
    int broadcastEnable=1;
    if ((bsocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        die("bsocket");
    }
    if (setsockopt(bsocket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) == -1)
    {
        die("setsockopt");
    }
    int reuse = 1;
    if (setsockopt(bsocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        die("setsockopt");
    }

    #ifdef SO_REUSEPORT
    if (setsockopt(bsocket, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1)
    {
        die("setsockopt");
    }
    #endif

    memset((char *) &baddr, 0, sizeof(baddr));
    baddr.sin_family = AF_INET;
    baddr.sin_port = htons(BROADCASTPORT);
    baddr.sin_addr.s_addr = inet_addr(BROADCASTIP);
    
 
    if( bind(bsocket, (struct sockaddr*)&baddr, sizeof(baddr)) == -1)
    {
            die("bbind");
    }
    

    //_------------------------------------------------------------------------
    // Local send/rcv connection
    //---------------------------------------------------------------------------
     
    if ((lsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("lsocket");
    }
    if (setsockopt(lsocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        die("setsockopt");
    }
    #ifdef SO_REUSEPORT
    if (setsockopt(lsocket, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1)
    {
        die("setsockopt");
    }
    #endif
    memset((char *) &laddr, 0, sizeof(laddr));
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(localPort);
    laddr.sin_addr.s_addr = INADDR_ANY;
    if( bind(lsocket, (struct sockaddr*)&laddr, sizeof(laddr) ) == -1)
    {
        die("lbind");
    }

    //_------------------------------------------------------------------------
    //Local ping/handshake connection
    //_------------------------------------------------------------------------

    if ((psocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("psocket");
    }
    if (setsockopt(psocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        die("setsockopt");
    }
    #ifdef SO_REUSEPORT
    if (setsockopt(psocket, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1)
    {
        die("setsockopt");
    }
    #endif
    memset((char *) &paddr, 0, sizeof(paddr));
    paddr.sin_family = AF_INET;
    paddr.sin_port = htons(PINGPORT);
    //
    paddr.sin_addr.s_addr = INADDR_ANY;
    if( bind(psocket, (struct sockaddr*)&paddr, sizeof(paddr) ) == -1)
    {
        die("pbind");
    }
    
    printf("Client successfully binded to localPort, pingport and broadcastport! \n" );
}


int udp_broadcaster(std::string message){
    struct sockaddr_in baddr;
    char * sbuff;
    sbuff = (char *) malloc(BUFLEN);
    memset(&sbuff[0], 0, sizeof(sbuff));
    strcat(sbuff, message.c_str());
    memset((char *) &baddr, 0, sizeof(baddr));
    baddr.sin_family = AF_INET;
    baddr.sin_port = htons(BROADCASTPORT);
    baddr.sin_addr.s_addr = inet_addr(BROADCASTIP);

    if (sendto(bsocket, sbuff, BUFLEN, 0, (struct sockaddr*) &baddr, sizeof(baddr)) == -1)
    {
        die("bcast");
    }
    return 0;

}

int udp_sender(std::string message, int localPort, char * reciever_ip) //master_ip = reciever_ip
{
    struct sockaddr_in addr;
    char sbuff[BUFLEN];
    memset(&sbuff[0], 0, sizeof(sbuff));
    strcat(sbuff, message.c_str());

    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(localPort);
    addr.sin_addr.s_addr = inet_addr(reciever_ip);
    if (sendto(lsocket, sbuff, BUFLEN, 0, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        die("sendto");
    }
    return 0;
}

int udp_handshake_sender(std::string message, int localPort, char * reciever_ip) //master_ip = reciever_ip
{
    struct sockaddr_in addr;
    char sbuff[BUFLEN];
    memset(&sbuff[0], 0, sizeof(sbuff));
    strcat(sbuff, message.c_str());

    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PINGPORT);
    addr.sin_addr.s_addr = inet_addr(reciever_ip);
    if (sendto(psocket, sbuff, BUFLEN, 0, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        die("sendto");
    }
    return 0;
}

struct code_message udp_reciever()
{
    struct sockaddr_in addr;
    int recv_len;
    socklen_t slen = sizeof(addr); 
    char rbuff[BUFLEN];
    struct code_message code;

    std::string data;
    std::string rip;
    
    // zero out the structure
    memset((char *) &addr, 0, sizeof(addr));
    
      
    memset(&rbuff[0], 0, sizeof(rbuff)); 

    if(recvfrom(lsocket, rbuff, BUFLEN, 0, (struct sockaddr *) &addr, &slen) == -1){
    	die("recvfrom");
    }
    data.assign(rbuff);
    code.data = data;
    rip.assign(inet_ntoa(addr.sin_addr));
    code.rip = rip;
    code.port = addr.sin_port;
    return code;
}


struct code_message udp_handshake_reciever()
{
    struct sockaddr_in addr;
    int recv_len;
    socklen_t slen = sizeof(addr); 
    char rbuff[BUFLEN];
    struct code_message code;
    code.responding = true;
    std::string data;
    std::string rip;
    
    memset((char *) &addr, 0, sizeof(addr));
    
    code.responding = true;

    memset(&rbuff[0], 0, sizeof(rbuff)); 
    struct timeval read_timeout;
    read_timeout.tv_sec = 2;
    read_timeout.tv_usec = 0;
    if(setsockopt(psocket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout)){
        die("setsockopt");
    }  
    if(recvfrom(psocket, rbuff, BUFLEN, 0, (struct sockaddr *) &addr, &slen) < 0)
    {
    	std::cout << "Timeout on handshake, elevator not responding!" << std::endl;
        code.responding = false; 
    }
    else{
        code.responding = true;
    }
    data.assign(rbuff);
    code.data = data;
    rip.assign(inet_ntoa(addr.sin_addr));
    code.rip = rip;
    code.port = addr.sin_port;

    return code;
}

struct code_message udp_recieve_broadcast(){
    int recv_len;
    struct code_message code;
    struct sockaddr_in addr;
    socklen_t slen = sizeof(addr);
    char rbuff [BUFLEN];
    std::string data;
    std::string rip;

    memset((char *) &addr, 0, sizeof(addr));
    memset(&rbuff[0], 0, sizeof(rbuff));
      
    if(recvfrom(bsocket, rbuff, BUFLEN, 0, (struct sockaddr *) &addr, &slen) == -1)
    {
        die("brecvfrom");
    }
    data.assign(rbuff);
    code.data = data;
    rip.assign(inet_ntoa(addr.sin_addr));
    code.rip = rip;
    code.port = addr.sin_port;
    return code; 
}

int bytes(){
    char buff[BUFLEN];
    return recv(bsocket, buff, BUFLEN, 0);
}

void udp_close(){
    close(bsocket);
    close(lsocket);
    close(psocket);
}

