#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "star_W.h"

int main() {
    pid_t fils = fork();
    srand(fils);
    if (fils == 0){
        combat(getppid());
    }
    else {
        combat(fils);
    }
    return 0;
}