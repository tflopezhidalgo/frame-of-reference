#ifndef READER_H_
#define READER_H_

#include <fstream>

#include "Block.h"
#include "ProtectedFile.h"

class Reader {
private:
  ProtectedFile *in;
  int32_t N;
  int32_t step;
  int32_t readed_to;
  int32_t offset;
  bool eof;

public:
  Reader(ProtectedFile *in, int32_t N, int32_t step, int32_t offset);
  Block<uint32_t> readBlock();
  bool canRead();
  ~Reader();
};

#endif
