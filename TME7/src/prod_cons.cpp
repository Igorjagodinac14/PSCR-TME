#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <vector>


using namespace std;
using namespace pr;

vector<pid_t> tokill;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

void kill_INT(int){
	for (auto p : tokill){
		kill(p,SIGINT);
	}
}

int main () {
	size_t shmsize = sizeof(Stack<char>);

	bool Anonyme = false;
	void* addr;


	if (Anonyme){
		addr = mmap(nullptr, shmsize,
		PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		if (addr == MAP_FAILED){
			perror("mmap Anonyme");
			exit(1);
		}
	} else {
		int fd = shm_open("/myshm", O_CREAT | O_EXCL | O_RDWR, 0666);
		if (fd <0){
			perror("shm_open");
			return 1;
		}
		if (ftruncate(fd,shmsize) != 0){
			perror("ftruncate");
			return 1;
		}

		addr = addr = mmap(nullptr, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

		if (addr == MAP_FAILED){
			perror("mmap anonyme");
			exit(1);
		}
	}
	Stack<char> * s = new (addr) Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	} else {
		tokill.push_back(pc);
	}

	signal(SIGINT, kill_INT);

	wait(0);
	wait(0);

	s->~Stack();
	if(munmap(addr,shmsize) != 0){
		perror("munmap");
		exit(1);
	}
	if( !Anonyme ){
		if (shm_unlink("/myshm") != 0 ){
			perror("sem");
		}
	}
	cerr << "\nFinish" << endl;
	return 0;
}

