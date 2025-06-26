#include <include/PageManager.h>

PageManager::PageManager(const char filename[]){
    this->fileStream.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if(!fileStream){
        throw std::runtime_error("Failed open file" + std::string(filename));
    }   
}