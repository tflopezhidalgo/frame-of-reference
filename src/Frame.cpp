#include "Frame.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include "Worker.h"
#include "Writer.h"

Frame::Frame(std::string in_f, std::string o_file, int32_t N, int32_t Q,
             int32_t T)
    : in(in_f), writer(o_file) {
  for (int i = 0; i < T; i++) {
    worker[i] = new Worker(&in, N, T, i, Q);
  }
  this->N = N;
  this->T = T;
}

void Frame::run() {
  for (int i = 0; i < T; i++)
    writer.addQueue(worker[i]->getQueue());

  writer.start();
  for (int i = 0; i < T; i++)
    worker[i]->start();

  for (int i = 0; i < T; i++)
    worker[i]->join();
  writer.join();
}

Frame::~Frame() {
  for (int i = 0; i < T; i++)
    delete worker[i];
}
