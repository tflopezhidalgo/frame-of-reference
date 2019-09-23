#ifndef BLOCK_H_
#define BLOCK_H_

#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <cstring>

template <class T>
class Block{

    private:
	    uint32_t block_size;
    	T data[100];
	    uint32_t reference;
    	uint8_t bit_size;
        bool EOF_block;

    public:
        
        Block(int32_t size) {
    	    this->block_size = size;
            for(int i = 0; i < 100; i++)
                data[i] = 0;
    	    this->reference = 0;
        	this->bit_size = 0;
            this->EOF_block = false;
        }
   
        Block(int32_t size, T* data) {
    	    this->block_size = size;
    	    this->setData(block_size, data);
            this->reference = 0;
        	this->bit_size = 0;
            this->EOF_block = false;
            this->setData(size, data);
        }

        Block(const Block& other){
            Block(other.block_size);
            this->block_size = other.block_size;
            memcpy(this->data, other.data, 100);
            this->reference = other.reference;
            this->bit_size = other.bit_size;
            this->EOF_block = other.EOF_block;
        }
    
        Block(const Block&& other){
            Block(other.block_size);
            this->block_size = other.block_size;
            memcpy(this->data, other.data, 100);
            this->reference = other.reference;
            this->bit_size = other.bit_size;
            this->EOF_block = other.EOF_block;
        }
   
        Block& operator=(const Block& other) = delete;

        Block&& operator=(const Block&& other) = delete;

        void setData(uint32_t size, T *data){
    	    for(uint32_t i = 0; i < size; i++)
    		    this->data[i] = data[i];
        }
    
        void setBitSize(uint8_t bit_size){
            this->bit_size = bit_size;
        }
    
        uint32_t findMin(){
    	    uint32_t min = UINT_MAX;
        	for(uint32_t i = 0; i < block_size; i++)
    	    	if(data[i] < min)
    		    	min = data[i];
    
        	this->reference = min;
    	    return min;
        }
    
        uint32_t findMax(){
    	    uint32_t max = 0;
        	for(uint32_t i = 0; i < block_size; i++)
    	    	if(data[i] > max)
    		    	max = data[i];
    
        	return max;
        }
    
        uint32_t getBlockSize(){
    	    return this->block_size;
        }
    
        T getWord(uint32_t index){
    	    return data[index];
        }
    
        void substract(uint32_t offset){
    
    	    for(uint32_t i = 0; i < block_size; i++)
        		data[i] = data[i] - offset;
        }
    
        uint32_t getReference(){
            return this->reference;
        }
    
        void setReference(uint32_t reference){
            this->reference = reference;
        }    
    
        uint8_t getBitSize(){
            return this->bit_size;
        }
    
        void setEOF(){
            this->EOF_block = true;
        }
    
        bool isEOF(){
            return this->EOF_block;
        }
    
        ~Block() {
        }
};

#endif
