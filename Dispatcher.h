#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Block.h"
#include "ProtectedQueue.h"

class Dispatcher {
private:
  ProtectedQueue queue;

public:
  explicit Dispatcher(uint32_t Q);
  ProtectedQueue *getQueue();
  void dispatch(Block<uint8_t> block);
  void sendEOF();
  ~Dispatcher();
};

#endif
