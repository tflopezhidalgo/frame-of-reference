#ifndef PROTECTEDFILE_H
#define PROTECTEDFILE_H

#include <fstream>
#include <string>
#include <mutex>
#include <cstdio>

class ProtectedFile{

private:
    
    std::mutex m;
    std::istream* in;
    std::ifstream file;

public:

    ProtectedFile(std::string filename);

    ProtectedFile(ProtectedFile& other) = delete;

    ProtectedFile& operator=(ProtectedFile& other) = delete;

    int32_t readBlock(uint32_t* buffer, int32_t from_pos, int32_t N);

    ~ProtectedFile();
};

#endif
