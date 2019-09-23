#include "Reader.h"

#include <fstream>
#include <vector>

#include "Block.h"
#include "ProtectedFile.h"

Reader::Reader(ProtectedFile *in, int32_t N, int32_t step, int32_t offset) {
  this->in = in;
  this->N = N;
  this->step = step;
  this->readed_to = 0;
  this->offset = offset;
  this->eof = false;
}

Block<uint32_t> Reader::readBlock() {
  std::vector<uint32_t> readed;

  in->readBlock(&readed, N * 4 * (offset + readed_to), N);

  if (readed.size())
    while (readed.size() < (uint32_t)N)
      readed.push_back(readed.back());
  else
    this->eof = true;

  readed_to = step + readed_to;
  return (Block<uint32_t>(readed));
}

bool Reader::canRead() { return !eof; }

Reader::~Reader() { in = NULL; }
