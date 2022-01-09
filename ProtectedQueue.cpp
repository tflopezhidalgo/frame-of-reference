#include "ProtectedQueue.h"

#include <mutex>
#include <queue>
#include <thread>

#include "Block.h"

ProtectedQueue::ProtectedQueue(uint32_t size) { this->size = size; }

void ProtectedQueue::push(Block<uint8_t> block) {
  std::unique_lock<std::mutex> lock(this->m);
  while (queue.size() == size) {
    cv.wait(lock);
  }

  this->queue.push(std::move(block));
  cv.notify_all();
}

Block<uint8_t> ProtectedQueue::pop() {
  std::unique_lock<std::mutex> lock(this->m);

  while (queue.empty()) {
    cv.wait(lock);
  }

  Block<uint8_t> element = this->queue.front();
  this->queue.pop();
  cv.notify_all();
  return element;
}

ProtectedQueue::~ProtectedQueue() {}
