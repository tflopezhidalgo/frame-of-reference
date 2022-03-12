#ifndef BLOCK_H_
#define BLOCK_H_

#include <limits.h>
#include <stdio.h>

#include <cstring>
#include <iostream>
#include <vector>

template <class T> class Block {
private:
  std::vector<T> data;
  uint32_t reference;
  uint8_t bit_size;
  bool EOF_block;

  uint32_t findMin() {
    uint32_t min = UINT_MAX;
    for (T i : data) {
      if (i < min) {
        min = i;
      }
    }
    this->reference = min;
    return min;
  }

  uint32_t findMax() {
    uint32_t max = 0;
    for (T i : data) {
      if (i > max) {
        max = i;
      }
    }

    return max;
  }

  void substract(uint32_t offset) {
    for (auto &i : data)
      i -= offset;
  }

  uint8_t countBits(uint32_t number) {
    uint8_t size = 0;

    while (number) {
      number = number >> 1;
      size++;
    }
    this->bit_size = size;
    return size;
  }

public:
  Block() { this->EOF_block = true; }

  explicit Block(std::vector<T> other) {
    this->data = other;
    this->reference = 0;
    this->bit_size = 0;
    this->EOF_block = false;
  }

  Block(const Block<T> &other) {
    this->data = other.data;
    this->reference = other.reference;
    this->bit_size = other.bit_size;
    this->EOF_block = other.EOF_block;
  }

  Block(const Block<T> &&other) {
    this->data = other.data;
    this->reference = other.reference;
    this->bit_size = other.bit_size;
    this->EOF_block = other.EOF_block;
  }

  Block &operator=(Block<T> &other) = delete;

  Block &operator=(Block<T> &&other) = delete;

  operator bool() const { return (this->data.size() > 0); }

  void setBitSize(uint8_t bit_size) { this->bit_size = bit_size; }

  uint8_t getMinRepr() {
    uint32_t min = findMin();
    substract(min);
    uint32_t max = findMax();
    return countBits(max);
  }

  uint32_t getBlockSize() { return data.size(); }

  T getWord(uint32_t index) { return data[index]; }

  std::vector<T> getValues() { return data; }

  uint32_t getReference() { return this->reference; }

  void setReference(uint32_t reference) { this->reference = reference; }

  uint8_t getBitSize() { return this->bit_size; }

  bool isEOF() { return this->EOF_block; }

  ~Block() {}
};

#endif
