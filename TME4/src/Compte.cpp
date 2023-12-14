#include "Compte.h"
#include <iostream>
using namespace std;

namespace pr {
recursive_mutex & Compte::getMutex(){
	return m;
}

void Compte::crediter (unsigned int val) {
	//unique_lock<mutex> g(m);
	if (this->getMutex().try_lock()){
		solde+=val ;
		this->getMutex().unlock();
	}
}
bool Compte::debiter (unsigned int val) {
	//unique_lock<mutex> g(m);
	bool doit = (unsigned)solde >= val;
	if (this->getMutex().try_lock()){
		if (doit) {
			solde-=val ;
		}
		this->getMutex().unlock();
	}
	return doit;
}
int Compte::getSolde() const  {
	//lock_guard<std::recursive_mutex> lk(m);
	//unique_lock<mutex> g(m);
	return solde;
}
// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte & other) {
	solde = other.solde;
}

}
