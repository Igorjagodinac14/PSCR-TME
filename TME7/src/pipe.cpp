#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    // creation des variables pour les deux lignes de commandes
    char* argv_1[argc];
    char* argv_2[argc];
    //Initialisation a 0 pour les deux variables
    memset(argv_1,0,argc * sizeof(char*));
    memset(argv_2,0,argc * sizeof(char*));

    int arg = 1;

    //boucle pour la premier ligne de commande
    for( ; arg < argc ; ++arg){
        if(! strcmp(argv[arg],"|")){
            arg++;
            break;
        }
        else{
            argv_1[arg-1] = argv[arg];
        }
    }

    //boucle pour la deuxieme ligne de commande
    for(int i = 0 ; arg < argc ; ++i, ++arg){
        argv_2[i] = argv[arg];
    }

    int tube[2];
    pid_t fils;

    if (pipe (tube) == -1){
        perror("pipe");
        exit(1);
    }

    //Fils 1 pour la ligne de commande n°1
    if ((fils = fork()) == -1){
        perror("fork");
        exit(2);
    }

    if (fils == 0){
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);
        close(tube[0]);

        cerr << "argv : ";
        for(int i =0; i< argc; ++i){
            if(argv_1[i] != nullptr){
                cerr << argv_1[i] << " ";
            }
            else {
                break;
            }
        }
        cerr << endl;
        if(execv (argv_1[0], argv_1) == -1){
            perror("execv");
            exit(3);
        }
    }

    //Fils 2 pour la ligne de commande n°2
    if ((fils = fork()) == -1){
        perror("fork");
        exit(2);
    }

    if (fils == 0){
        dup2(tube[0], STDIN_FILENO);
        close(tube[0]);
        close(tube[1]);

        cerr << "argv : ";
        for(int i =0; i< argc; ++i){
            if(argv_2[i] != nullptr){
                cerr << argv_2[i] << " ";
            }
            else {
                break;
            }
        }
        cerr << endl;
        if(execv (argv_2[0], argv_2) == -1){
            perror("execv");
            exit(3);
        }
    }

    //PERE
    close(tube[0]);
    close(tube[1]);

    wait(0);
    wait(0);
    return 0;
}