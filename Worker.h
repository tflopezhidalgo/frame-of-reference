#ifndef WORKER_H_
#define WORKER_H_

#include "Thread.h"
#include "Compressor.h"
#include "Reader.h"
#include "Dispatcher.h"
#include "ProtectedQueue.h"
#include "ProtectedFile.h"
#include <fstream>

class Worker: public Thread{
    private:
	    Reader reader;
    	Compressor compressor;
	    Dispatcher dispatcher;

    public:
	    Worker(ProtectedFile* in, 
               int32_t N, 
               int32_t step, 
               int32_t offset, 
               int32_t Q);
        virtual void run() override;
        ProtectedQueue* getQueue();
    	~Worker();
};

#endif
