#include "Dispatcher.h"

#include "Block.h"
#include "ProtectedQueue.h"

Dispatcher::Dispatcher(uint32_t Q) : queue(Q) {}

ProtectedQueue *Dispatcher::getQueue() { return &this->queue; }

void Dispatcher::dispatch(Block<uint8_t> block) { this->queue.push(block); }

Dispatcher::~Dispatcher() {}
