#pragma once
#include <iostream>
#include <thread>
#include <condition_variable>

namespace pr {

class Barrier {
	size_t count;
	const size_t N;
	mutable std::mutex m;
    std::condition_variable cv;

public:
	Barrier(size_t num) :count(0), N(num) {}

	void done(){
        std::unique_lock<std::mutex> lg(m);
        count++;
        if (count == N){
            cv.notify_all();
        }
    }
    void waitfor(){
        std::unique_lock<std::mutex> lg(m);
        while(count != N){
            cv.wait(lg);
        }
    }
};
}