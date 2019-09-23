#include "Frame.h"
#include "Writer.h"
#include "Worker.h"
#include <iostream>
#include <mutex>
#include <fstream>
#include <cstdio>

Frame::Frame(std::string in_f, 
             std::string o_file, 
             int32_t N, 
             int32_t Q, 
             int32_t T) :
             in(in_f),
             worker1(&in, N, 3, 0, Q),
             worker2(&in, N, 3, 1, Q),                   
             worker3(&in, N, 3, 2, Q), 
             writer(o_file){

    this->N = N;
    this->T = T;
    
}

void Frame::run(){

   writer.addQueue(worker1.getQueue());
   writer.addQueue(worker2.getQueue());
   writer.addQueue(worker3.getQueue());

    writer.start();
    worker1.start(); 
    worker2.start();
    worker3.start();

    worker3.join();
    worker2.join();
    worker1.join();
    writer.join();

}

Frame::~Frame() {
}

