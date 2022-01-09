#ifndef FRAME_H_
#define FRAME_H_

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ProtectedFile.h"
#include "Worker.h"
#include "Writer.h"

class Frame {
private:
  ProtectedFile in;
  int32_t N;
  int32_t T;
  Worker *worker[10];
  Writer writer;

public:
  Frame(std::string in_f, std::string o_file, int32_t N, int32_t Q, int32_t T);
  void run();
  ~Frame();
};

#endif
