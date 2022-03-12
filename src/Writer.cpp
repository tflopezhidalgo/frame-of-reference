#include "Writer.h"

#include <arpa/inet.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ProtectedQueue.h"

Writer::Writer(std::string o_file) {
  if (o_file == "-") {
    this->out = &std::cout;
  } else {
    this->out_file.open(o_file, std::fstream::binary);
    this->out = &out_file;
  }
}

void Writer::addQueue(ProtectedQueue *queue) { this->queues.push_back(queue); }

void Writer::run() {
  uint8_t idx = 0;

  while (!queues.empty()) {
    if (idx >= (queues.size()))
      idx = 0;

    Block<uint8_t> block = queues[idx]->pop();
    if (block.isEOF()) {
      queues.erase(queues.begin() + idx);
    } else {
      uint32_t buffer = htonl(block.getReference());
      out->write((char *)&buffer, 4);
      *out << block.getBitSize();

      for (uint8_t sample : block.getValues())
        *out << sample;
    }

    idx++;
  }
}

Writer::~Writer() {
  if (out_file) {
    out_file.close();
  }
}
