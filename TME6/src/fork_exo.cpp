#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int nbfils = 0;
	for (int i=1, j=N; i<=N && j==N ; i++ ) {
		if (fork() == 0){
			nbfils =0 ;
			std::cout << " i:j " << i << ":" << j << std::endl;
			for (int k=1; k<=i && j==N ; k++) {
				if ( fork() == 0) {
					nbfils =0;
					j=0;
					std::cout << " k:j " << k << ":" << j << std::endl;
				}
				else {
					nbfils++;
				}
			}
		} 
		else {
			nbfils++;
			break;
		}
	}	
	//std::cout << "NB fils = " << nbfils << " pour pid  = " << getpid() << std::endl;
	for (int i = 0; i < nbfils; ++i){
		if (wait(NULL) == -1){ std::cerr << "Trop de wait de " << getpid() << std::endl;}
	}
	if (wait(NULL) != -1){ std::cerr << "il y en reste : " << getpid() << std::endl;}
	return 0;
}

//Q1 : Il y a 10 processus (dont 9 processus fils)
// Le processus pére crée un processus fils et qui crée aprés N fils selon si c'est le 1er ou non
