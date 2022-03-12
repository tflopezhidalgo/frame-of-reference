#ifndef PROTECTED_QUEUE_H_
#define PROTECTED_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

#include "Block.h"

class ProtectedQueue {
private:
  std::queue<Block<uint8_t>> queue;
  std::condition_variable cv;
  std::mutex m;
  uint32_t size;

public:
  explicit ProtectedQueue(uint32_t size);
  void push(Block<uint8_t> block);
  Block<uint8_t> pop();
  ~ProtectedQueue();
};

#endif
