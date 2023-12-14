#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Queue.h"
#include "Job.h"
#include "Pool.h"
#include "Barrier.h"

using namespace std;
using namespace pr;

int main(){
    /*
    int ret = 0;
    Barrier b(10);
    Job * j = new SleepJob(42,&ret);
    thread t(&Job::run,j);
    t.join();
    cout << ret << endl;
    delete j;
    */

    const int TAILLE_THREADS = 20;
    const int JOB_NUMBER = 60;

    Pool pool(15);
    vector<int> result_job(JOB_NUMBER);
    pool.start(TAILLE_THREADS);
    Barrier bar(JOB_NUMBER);

    for(int i= 0; i < JOB_NUMBER; ++i){
        pool.submit(new SleepJobBarrier(i,&result_job[i],&bar));
    }

    bar.waitfor();
    pool.stop();

    for(int &result : result_job){
        cout<< result << " , " ;
    }
    cout <<endl;
}