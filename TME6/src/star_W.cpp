#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "star_W.h"
#include "rsleep.h"
using namespace std;

int point_de_vie = 3;
void action(int signal){
    if(signal == SIGINT){
        point_de_vie--;
        cout << "Coup recu !" << endl;
        if (point_de_vie == 0){
            cout << "Adversaire battu avec le pid =" << getpid() << endl;
            exit(1);
        }
    }
}

void attaque (pid_t adversaire){
    signal(SIGINT,action);
    if (kill(adversaire,SIGINT)<0){
        cout << "Adversaire déja mort, avec le pid = " << adversaire <<endl;
        exit(0);
    }
    randsleep();
}

void defense(){
    signal(SIGINT,SIG_IGN);
    /*
    sleep(rand()% 3);
    */
    randsleep();
}

void combat(pid_t adversaire){
    while(true){
        defense();
        attaque(adversaire);
    }
}