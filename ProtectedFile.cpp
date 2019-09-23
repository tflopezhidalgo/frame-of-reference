#include "ProtectedFile.h"
#include <string>
#include <mutex>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <cstdio>

ProtectedFile::ProtectedFile(std::string filename){ 
            if(filename == "-"){
                this->in = &std::cin;
            }else{
                this->file.open(filename, std::fstream::binary);
                this->in = &file;
            }
}

int32_t ProtectedFile::readBlock(uint32_t* buffer, int32_t from_pos, int32_t N){
    std::unique_lock<std::mutex> lck(m);
    in->clear();
    in->seekg(from_pos, in->beg);

    int32_t idx = 0;

    while (idx < N && in->read((char *)&buffer[idx], 4)){
        buffer[idx] = ntohl(buffer[idx]);
        for (int32_t i = idx; i < N; i++)
            buffer[i] = buffer[idx];
        idx++;
    }

    if(idx == 0){
        return 2;
    }

    char test;
    *in >> test;
    if(in->eof()){
        return 1;
    }else if(in->fail()){
        return 2;
    }else{
        return 0;
    }
}


ProtectedFile::~ProtectedFile(){

    if(file)
        file.close(); 

}
