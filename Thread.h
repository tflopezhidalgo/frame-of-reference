#ifndef THREAD_H_
#define THREAD_H_

#include <thread>

#include "ProtectedQueue.h"

class Thread {
private:
  std::thread thread;

public:
  Thread() {}
  void start();
  virtual void run() = 0;
  void join();
  Thread(const Thread &) = delete;
  Thread &operator=(const Thread &) = delete;
  Thread(Thread &&other) { this->thread = std::move(other.thread); }
  Thread &operator=(Thread &&other) {
    this->thread = std::move(other.thread);
    return *this;
  }
  virtual ~Thread() {}
};

#endif
