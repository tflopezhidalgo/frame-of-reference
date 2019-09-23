#ifndef WORKER_H_
#define WORKER_H_

#include <fstream>

#include "Compressor.h"
#include "Dispatcher.h"
#include "ProtectedFile.h"
#include "ProtectedQueue.h"
#include "Reader.h"
#include "Thread.h"

class Worker : public Thread {
private:
  Reader reader;
  Compressor compressor;
  Dispatcher dispatcher;

public:
  Worker(ProtectedFile *in, int32_t N, int32_t step, int32_t offset, int32_t Q);
  virtual void run() override;
  ProtectedQueue *getQueue();
  ~Worker();
};

#endif
