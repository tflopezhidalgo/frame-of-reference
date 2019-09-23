#include "Worker.h"

#include <fstream>
#include <iostream>

#include "Block.h"
#include "ProtectedFile.h"
#include "ProtectedQueue.h"
#include "Reader.h"

Worker::Worker(ProtectedFile *in, int32_t N, int32_t step, int32_t offset,
               int32_t Q)
    : reader(in, N, step, offset), dispatcher(Q) {}

void Worker::run() {
  while (reader.canRead()) {
    Block<uint32_t> block = reader.readBlock();
    if (block) {
      Block<uint8_t> compressed = compressor.compress(block);
      dispatcher.dispatch(compressed);
    }
  }
  Block<uint8_t> eof;
  dispatcher.dispatch(eof);
}

ProtectedQueue *Worker::getQueue() { return this->dispatcher.getQueue(); }

Worker::~Worker() {}
