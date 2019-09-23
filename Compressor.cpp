#include "Compressor.h"
#include "Block.h"
#include <arpa/inet.h>
#include <bitset>
#include <vector>
#include <queue>

Block<uint8_t> Compressor::compress(Block<uint32_t> block){
	uint32_t min = block.findMin();
	block.substract(min);
	uint32_t max = block.findMax();
	uint8_t bit_size = this->countBits(max);
    int32_t packed_size = bit_size * block.getBlockSize();
    int32_t padding = 0;

    while((packed_size + padding) % 8)
        padding++;

    //std::bitset<BUFFER_SIZE> buffer;
    std::vector<bool> buffer;
	for(uint32_t i = 0; i < block.getBlockSize() ; i++){
		this->reduce(&buffer, block.getWord(block.getBlockSize() - i -1 ), bit_size);
    }
 //   buffer = buffer << padding; 
    for(int i = 0; i < padding; i++)
        buffer.push_back(0);

    int32_t total_bytes = (packed_size + padding) / 8;
//    uint32_t numero = buffer.to_ulong();

    uint8_t *buff1 =  new uint8_t[total_bytes];
//    uint8_t *buff2 = (uint8_t *)&numero;
    
    for(int32_t i = 0; i < total_bytes; i++)
//        buff1[total_bytes - 1 - i] = buff2[i];
        setByte(&buff1[i], &buffer);

    Block<uint8_t> out(total_bytes, buff1);
    out.setBitSize(bit_size);
    out.setReference(min);

    delete[] buff1;
    return out;
}

void Compressor::setByte(uint8_t* buf1, std::vector<bool> *buffer){
           
    for(int i = 0; i < 8; i++){
        bool e = buffer->back();
        buffer->pop_back();
        if(e)
            *buf1 = *buf1 + 1;
        if(i != 7)
            *buf1 = *buf1 << 1;
    }
//    swapByte(buf1);
}

void Compressor::swapByte(uint8_t* byte){

       *byte = (*byte & 0xF0) >> 4 | (*byte & 0x0F) << 4;
       *byte = (*byte & 0xCC) >> 2 | (*byte & 0x33) << 2;
       *byte = (*byte & 0xAA) >> 1 | (*byte & 0x55) << 1;
}

void Compressor::reduce(std::vector<bool> *buffer, 
                        uint32_t number, 
                        uint8_t bit_size){
/*    std::bitset<BUFFER_SIZE> aux(number);
    *buffer = *buffer << bit_size;
	*buffer = *buffer | aux;
    std::cout << "bitset vale " << buffer->to_string() <<
        " y tamanio " << buffer->size() << std::endl;*/
    for (int i = 0; i < bit_size; i++){
        buffer->push_back(number % 2);
        number = number >> 1;
    }


}

uint8_t Compressor::countBits(uint32_t number){
	uint8_t size = 0;

	while (number){
		number = number >> 1;
		size++;
	}
	return size;
}

