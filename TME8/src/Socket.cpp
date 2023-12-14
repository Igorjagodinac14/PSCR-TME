#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <string>
#include <iosfwd>
#include <unistd.h>
#include "Socket.h"

namespace pr {
void Socket::connect(in_addr ipv4, int port){
    auto fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(fd <0){perror("socket");}
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr = ipv4;
    if (::connect(fd,(struct sockaddr *)&server,sizeof(server))<0){
        fd = -1;
        perror("connect");
    }
}

void Socket::connect(const std::string & host, int port){
    struct addrinfo * adr;
    if (getaddrinfo(host.c_str(),nullptr,nullptr,&adr)){
        perror("DNS");
    }
    for(struct addrinfo * np = adr; np != NULL;np = np->ai_next){
        if(np->ai_family == AF_INET && np->ai_socktype == SOCK_STREAM){
            auto ipv4 = ((struct sockaddr_in *)np->ai_addr)->sin_addr;
            freeaddrinfo(adr);
            connect(ipv4,port);
            break;
        }
    }
}


void Socket::close(){
    if(this->fd != -1){
        ::close(fd);
        fd = -1;
        shutdown(fd,2);
    }
}
}