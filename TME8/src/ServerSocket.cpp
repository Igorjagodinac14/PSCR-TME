#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/types.h>
#include <sys/un.h>
using namespace std;
namespace pr {

ServerSocket::ServerSocket(int port){
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if (socketfd <0){perror("socket");}

    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_family = INADDR_ANY;
    if (bind(socketfd,(struct sockaddr *) & adr,sizeof(adr))<0){
        perror("bind");
    }
    if (listen(socketfd,10)<0){
        perror("listen");
        close();
    }
}

Socket ServerSocket::accept(){
    struct sockaddr_in exp;
    socklen_t taille = sizeof(exp);
    int sc = ::accept(this->socketfd,(struct sockaddr*)&exp,&taille);
    cout << "Connection de" << &exp;
    return Socket(sc);
}

void ServerSocket::close(){
    if(this->socketfd != -1){
        ::close(socketfd);
        socketfd = -1;
        shutdown(socketfd,2);
    }
}
ostream & operator <<(ostream &os, struct sockaddr_in * adr){
    char host[1024];
    if (getnameinfo((struct sockaddr *)&adr, sizeof(adr),host,1024,nullptr,0,0)){
        os << "host" << host << endl;
    }
    cout << inet_ntoa(adr->sin_addr)<<":"<<ntohs(adr->sin_port);
    return os;
}
}