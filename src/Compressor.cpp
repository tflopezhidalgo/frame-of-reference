#include "Compressor.h"

#include <vector>

#include "Block.h"

Block<uint8_t> Compressor::compress(Block<uint32_t> block) {
  block.getMinRepr();
  int32_t packed_size = block.getBitSize() * block.getBlockSize();
  int32_t padding = 0;

  while ((packed_size + padding) % 8)
    padding++;

  std::vector<bool> buffer;
  for (int i = 0; i < padding; i++) {
    buffer.push_back(0);
  }

  for (uint32_t i = 0; i < block.getBlockSize(); i++) {
    this->reduce(&buffer, block.getWord(block.getBlockSize() - i - 1),
                 block.getBitSize());
  }

  std::vector<uint8_t> out;

  while (buffer.size()) {
    uint8_t buff = 0;
    setByte(&buff, &buffer);
    out.push_back(buff);
  }

  Block<uint8_t> compressed(out);
  compressed.setBitSize(block.getBitSize());
  compressed.setReference(block.getReference());

  return compressed;
}

void Compressor::setByte(uint8_t *buf1, std::vector<bool> *buffer) {
  for (int i = 0; i < 8; i++) {
    bool e = buffer->back();
    buffer->pop_back();
    if (e)
      *buf1 = *buf1 + 1;
    if (i != 7)
      *buf1 = *buf1 << 1;
  }
}

void Compressor::reduce(std::vector<bool> *buffer, uint32_t number,
                        uint8_t bit_size) {
  for (int i = 0; i < bit_size; i++) {
    buffer->push_back(number % 2);
    number = number >> 1;
  }
}
