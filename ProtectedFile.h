#ifndef PROTECTEDFILE_H
#define PROTECTEDFILE_H

#include <fstream>
#include <string>
#include <mutex>
#include <cstdio>
#include <vector>

class ProtectedFile{
    private:
        std::mutex m;
        std::istream* in;
        std::ifstream file;

    public:
        explicit ProtectedFile(std::string filename);
        ProtectedFile(ProtectedFile& other) = delete;
        void readBlock(std::vector<uint32_t>* buffer, 
                       int32_t from_pos, 
                       int32_t N);
        ~ProtectedFile();
};

#endif
