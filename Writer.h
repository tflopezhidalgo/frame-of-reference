#ifndef WRITER_H_
#define WRITER_H_

#include "ProtectedQueue.h"
#include "Thread.h"
#include <fstream>
#include <vector>
#include <string>

class Writer: public Thread{
    private:
        std::ostream* out;
        std::ofstream out_file;
        std::vector<ProtectedQueue*> queues;

    public:
	    explicit Writer(std::string o_file);
        void addQueue(ProtectedQueue* queue);
        virtual void run() override;
    	~Writer();
};

#endif
