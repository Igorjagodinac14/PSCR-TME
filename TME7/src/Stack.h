#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
#include <iostream>
namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t mutex;
	sem_t sem_pop;
	sem_t sem_push;
public :
	Stack () : sz(0) { 
		sem_init(&mutex,1,1);
		sem_init(&sem_pop,1,0);
		sem_init(&sem_push,1,STACKSIZE);
		memset(tab,0,sizeof tab) ;
	}

	T pop () {
		// bloquer si vide
		sem_wait(&sem_pop);
		sem_wait(&mutex);
		T toret = tab[--sz];
		sem_post(&mutex);
		sem_post(&sem_push);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&sem_push);
		sem_wait(&mutex);
		tab[sz++] = elt;
		sem_post(&mutex);
		sem_post(&sem_pop);
	}

	~Stack() {
		sem_destroy(&mutex);
		sem_destroy(&sem_pop);
		sem_destroy(&sem_push);
	}
};

}
