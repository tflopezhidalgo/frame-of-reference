#include "Writer.h"
#include "ProtectedQueue.h"
#include <fstream>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <cstdio>

Writer::Writer(std::string o_file) {
    if(o_file == "-"){
        this->out = &std::cout;
        this->in_file = false;
    }else{
        this->out_file.open(o_file, std::fstream::binary);
        if(!out_file.is_open())
                out_file.close();
        this->out = &out_file;
        this->in_file = true;
    }

}

void Writer::addQueue(ProtectedQueue* queue){
    this->queues.push_back(queue);
}

void Writer::run() {
    bool cont = true;
    while (cont){
        for(uint32_t i = 0; i < queues.size(); i++){
            Block<uint8_t> to_write = queues[i]->pop();
            if (to_write.isEOF()){
                queues.erase(queues.begin()+i);
                break;
            }else{

                uint32_t buffer = htonl(to_write.getReference());
                out->write((char*)&buffer, 4);
                *out << to_write.getBitSize();

                for (uint32_t i = 0; i < to_write.getBlockSize(); i++)
                    *out << to_write.getWord(i);
            }
        }

        if(queues.empty())
            cont = false;
    }
}

Writer::~Writer() {
    if(in_file){
        out_file.close();
    }
}

