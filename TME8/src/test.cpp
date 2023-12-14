#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#define PORT 2121
#define N 10

int createServerSocket(int port){
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = INADDR_ANY;
    int fd = socket(AF_INET,SOCK_STREAM,0);
    bind(fd,(struct sockaddr *) &sa, sizeof(sa));
    listen(fd,10);
    return fd;
}

int main(){
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = INADDR_ANY;
    int fromlen = sizeof(sa);
    int fdr = createServerSocket(3000);
    //int fdw = createServerSocket(4000);
    char buff[256];
    while(1){
        int w = accept(fdr,(struct sockaddr *) &sa,(socklen_t *)&fromlen);
        read(w,buff,256);
        shutdown(w,2);
        close(w);
       /* for (int i = 0; i< N;i++){
            int n = accept(fdw,(struct sockaddr *) &sa,(socklen_t *)&fromlen);
            write(n,buff,256);
            shutdown(n,2);
            close(n);
        }*/
    }
}