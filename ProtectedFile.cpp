#include "ProtectedFile.h"

#include <arpa/inet.h>

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

ProtectedFile::ProtectedFile(std::string filename) {
  if (filename == "-") {
    this->in = &std::cin;
  } else {
    this->file.open(filename, std::fstream::binary);
    this->in = &file;
  }
}

void ProtectedFile::readBlock(std::vector<uint32_t> *buffer, int32_t from_pos,
                              int32_t N) {
  std::unique_lock<std::mutex> lck(m);
  int32_t idx = 0;
  uint32_t value = 0;

  in->clear();
  in->seekg(from_pos, in->beg);

  while (idx < N && in->read((char *)&value, 4)) {
    buffer->push_back(ntohl(value));
    idx++;
  }
}

ProtectedFile::~ProtectedFile() {
  if (file) file.close();
}
