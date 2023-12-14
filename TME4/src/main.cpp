#include "Banque.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <forward_list>

using namespace std;

const int NB_THREAD = 10;
int main () {
	srand(time(nullptr));
	pr::Banque b(100,1000);
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	for(size_t i = 0; i < NB_THREAD; ++i){
		size_t value = rand() % 100;
		size_t c1 = rand()% 100;
		size_t c2 = rand()% 100;
		threads.emplace_back(&pr::Banque::transfert,&b,c1,c2,value);
	}
	//this_thread::sleep_for(chrono::milliseconds(rand()*20));
	for (auto & t : threads) {
		t.join();
		b.comptabiliser(100000);
	}
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
