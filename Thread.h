#ifndef THREAD_H_
#define THREAD_H_

#include <thread>

class Thread {

private:
    std::thread thread;

public:
    
    void start();

    virtual void run() = 0;
    
    void join();
};

#endif
