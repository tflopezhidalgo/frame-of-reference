#ifndef FRAME_H_
#define FRAME_H_

#include <string>
#include <fstream>
#include <vector>
#include "Worker.h"
#include "Writer.h"
#include "ProtectedFile.h"
#include <iostream>
#include <cstdio>

class Frame {

private:
    ProtectedFile in;
	int32_t N;
	int32_t Q;
	int32_t T;
    Worker worker1;
    Worker worker2;
    Worker worker3;
    Writer writer;

public:
	Frame(std::string in_f, 
          std::string o_file, 
          int32_t N, 
          int32_t Q, 
          int32_t T);

    void run();

	~Frame();
};

#endif
