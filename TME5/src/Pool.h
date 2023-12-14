#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <cstring>
#include <thread>
using namespace std;
namespace pr {
	void poolWorker(Queue<Job> *queue){
    	while(true){
        	Job* j = queue->pop();
        	if(j == nullptr) {
				break;
			}
        	j->run();
        	delete j;
    	}
	}
class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:	
	Pool(int qsize) : queue(qsize){}

	void start(int nbt){
        threads.reserve(nbt);
        for(int i = 0; i<nbt; ++i){
            threads.emplace_back(&poolWorker,&queue);
        }
    }

	void stop(){
        queue.set_Blocking(false);
        for(auto & t : threads){
            t.join();
        }
        threads.clear();
    }

    void submit(Job * j){queue.push(j);}


	~Pool(){stop();}
};

}
