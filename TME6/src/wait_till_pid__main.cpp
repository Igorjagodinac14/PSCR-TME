#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

pid_t wait_till_pid(pid_t pid){
    for(;;){
        pid_t p = wait(nullptr);
        if(p ==-1 || p == pid){
            return p;
        }
    }
}

pid_t wait_till_pid_sec(pid_t pid,int sec){
    static bool timeout;
    signal(SIGALRM,[](int){cout << "SIGALRM recu" <<endl; timeout = true;});
    signal(SIGCHLD,[](int){cout << "SIGCHLD recu" <<endl;});
    alarm(sec);
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set,SIGALRM);
    sigdelset(&set,SIGCHLD);

    for(;;){
        cout << "Wait !" << endl;
        sigsuspend(&set);
        if (timeout){
            cout << "Alarm !" << endl;
            return -1;
        } else {
            pid_t p = wait(nullptr);
            if(p == pid){
                alarm(0);
            }
            if(p ==-1){
                return p;
            }
        }
    }
}

int main(){
    pid_t fils = fork();
    if (fils == 0){
        sleep(5);
    } else {
        signal(SIGINT,[] (int) {});
        pid_t result = wait_till_pid_sec(fils,3);
        cout << "wait donne " << result << endl;
    }
    return 0;
}