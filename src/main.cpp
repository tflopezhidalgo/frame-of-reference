#include <iostream>
#include <string>

#include "Frame.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    return printf(
      "No args received.\n"
      "Usage: %s <block size> <queue size> <concurrency> <target> <output_file>",
      argv[0]
    );
  }

  try { 
    Frame frame(
      argv[4], argv[5], std::atoi(argv[1]), std::atoi(argv[2]), std::atoi(argv[3])
    );
    frame.run();

  } catch(std::exception e) {
    return printf("Failed to compress. Error : %s", e.what());
  }
}
