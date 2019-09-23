#include "Reader.h"
#include "Block.h"
#include <fstream>
#include <netinet/in.h>
#include <iostream>
#include "ProtectedFile.h"

Reader::Reader(ProtectedFile* in, int32_t N, int32_t step, int32_t offset) {
    this->in = in;
    this->N = N;
    this->step = step;
    this->readed_to = 0;
    this->offset = offset;
    this->eof_next = false;
    this->error_seted = false;
}

Block<uint32_t> Reader::readBlock(){
    Block<uint32_t> readed_block(this->N); 
    uint32_t *buffer = new uint32_t[N];

    int32_t error = in->readBlock(buffer, N * 4 * (offset + readed_to), N);

    if(error == 1){
        eof_next = true;
        this->error_seted = false;
    }else if(error == 2){
        this->error_seted = true;
        eof_next = true;
    }

    readed_to = step + readed_to;
    readed_block.setData(N, buffer);
    delete[] buffer;
    return readed_block;
}

bool Reader::canRead(){
    return (!eof_next && !error_seted);
}

bool Reader::error_set(){
    return (this->error_seted);
}

Reader::~Reader() {

}

