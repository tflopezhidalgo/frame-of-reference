#include <iostream>
#include <string>

#include "Frame.h"

int main(int argc, char *argv[]) {
  Frame frame(argv[4], argv[5], std::atoi(argv[1]), std::atoi(argv[2]),
              std::atoi(argv[3]));
  frame.run();
}
