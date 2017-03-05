#include "udp_sendrec.h"

int bsocket, lsocket, msocket;

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
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
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
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
            std::string temp(addressBuffer);
            ip = temp;
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    
    return ip;
}

//sendPort = MASTERPORT
//recvPort = SLAVEPORT
void udp_init(int localPort, int elevator_role){
    struct sockaddr_in laddr, baddr;
    
     //_------------------------------------------------------------------------
    // broadcast
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
    

    memset((char *) &baddr, 0, sizeof(baddr));
    baddr.sin_family = AF_INET;
    baddr.sin_port = htons(BROADCASTPORT);
    baddr.sin_addr.s_addr = inet_addr(BROADCASTIP);
    
    //Bind to broadcast socket if role is slave
    if(elevator_role == 0){ //role = 0 ----> slave
        if( bind(bsocket, (struct sockaddr*)&baddr, sizeof(baddr)) == -1)
        {
            die("bbind");
        }
    }
    

    //_------------------------------------------------------------------------
    // local send/rcv
    //---------------------------------------------------------------------------
    if ((lsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("lsocket");
    }
    memset((char *) &laddr, 0, sizeof(laddr));
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(localPort);
    //

    //Bind to socket if role = master <=> elevator_role = 1
    if(elevator_role == 1){
        laddr.sin_addr.s_addr = INADDR_ANY;
        if( bind(lsocket, (struct sockaddr*)&laddr, sizeof(laddr) ) == -1)
        {
        die("lbind");
        }
    }else{
        laddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    

    
    printf("Client successfully binded to localPort and broadcastport! \n" );
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
        //printf("Data from sender: %s\n" , sbuff);

    return 0;

}

int udp_sender(std::string message, int localPort, char * ip)
{
    struct sockaddr_in addr;
    char sbuff[BUFLEN];
    memset(&sbuff[0], 0, sizeof(sbuff));
    strcat(sbuff, message.c_str());

    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(localPort);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (sendto(lsocket, sbuff, BUFLEN, 0, (struct sockaddr*) &addr, sizeof(addr)) == -1)
    {
        die("sendto()");

        
    }
        //printf("Data from sender: %s\n" , sbuff);    
 
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
    //try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(lsocket, rbuff, BUFLEN, 0, (struct sockaddr *)&addr, &slen)) == -1)
    {
        die("recvfrom()");
    }
    data.assign(rbuff);
    code.data = data;
    rip.assign(inet_ntoa(addr.sin_addr));
    code.rip = rip;
    code.port = addr.sin_port;

    //printf("Data received: %s \n" , rbuff);
 
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
    if((recv_len = recvfrom(bsocket, rbuff, BUFLEN, 0, (struct sockaddr *) &addr, &slen)) == -1)
    {
        die("recvfrombcast");
    }
    data.assign(rbuff);
    code.data = data;
    rip.assign(inet_ntoa(addr.sin_addr));
    code.rip = rip;
    code.port = addr.sin_port;

    //code.data = (char *) malloc(sizeof(char)*recv_len);
    //memcpy(code.data, rbuff, sizeof(rbuff));
    //code.rip= inet_ntoa(addr.sin_addr);

    //printf("Data received: %s\n" , rbuff);
    return code; 
}

int bytes(){
    char buff[BUFLEN];
    return recv(bsocket, buff, BUFLEN, 0);
}

void udp_close(){
    close(bsocket);
    close(lsocket);
}

