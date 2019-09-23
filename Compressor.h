#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include <bitset>
#include <vector>

#include "Block.h"

#define BUFFER_SIZE 32

class Compressor {
public:
  Block<uint8_t> compress(Block<uint32_t> block);
  void reduce(std::vector<bool> *buffer, uint32_t number, uint8_t bit_size);
  void setByte(uint8_t *buf1, std::vector<bool> *buffer);
};

#endif
