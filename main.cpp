#include <iostream>
#include "Frame.h"
#include <string>

int main(int argc, char *argv[]){

    // 4 1 1 entrada salida 

    Frame frame(argv[4], 
                argv[5], 
                std::atoi(argv[1]), 
                std::atoi(argv[2]), 
                std::atoi(argv[3])); 

    frame.run();

}
