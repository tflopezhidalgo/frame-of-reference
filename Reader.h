#ifndef READER_H_
#define READER_H_

#include "Block.h"
#include "ProtectedFile.h"
#include <fstream>

class Reader {

private:
    ProtectedFile* in;
    int32_t N;
    int32_t step;
    int32_t readed_to;
    int32_t offset;
    bool eof_next;
    bool error_seted;

public:
	Reader(ProtectedFile* in, 
           int32_t N, 
           int32_t step,
           int32_t offset);
    Block<uint32_t> readBlock();
    bool canRead();
    bool error_set();
	~Reader();
};

#endif
