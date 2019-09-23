#include "Worker.h"
#include "ProtectedQueue.h"
#include "ProtectedFile.h"
#include "Block.h"
#include "Reader.h"
#include <fstream>
#include <iostream>

Worker::Worker(ProtectedFile* in, 
               int32_t N, 
               int32_t step, 
               int32_t offset, 
               int32_t Q) : 
               reader(in, N, step, offset), 
               dispatcher(Q) {  }

void Worker::run(){
    
    while (reader.canRead()){
        Block<uint32_t> block = reader.readBlock();
        if(!reader.error_set()){
            Block<uint8_t> compressed_block = compressor.compress(block);
            dispatcher.dispatch(compressed_block);
        }
    }

    Block<uint8_t> EOF_b(0);
    EOF_b.setEOF();
    dispatcher.dispatch(EOF_b);
}

ProtectedQueue* Worker::getQueue(){
    return this->dispatcher.getQueue();
}

Worker::~Worker(){

}

