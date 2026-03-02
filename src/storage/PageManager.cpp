//
// Created by Jefferson on 22/08/2025.
//
#include "include/PageManager.h"

#include <cstring>
#include <iostream>

#include "include/Page.h"
#include "include/Registro.h"

PageManager::PageManager(const char *filename) {
    this->pageManager.open(filename, std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary);

    if (!this->pageManager) {
        std::cerr << "Failed open file" << std::endl;
        throw std::runtime_error("Failed open file " + std::string(filename));
    }
}
void PageManager::writePage(const Page &page) {
    char bufferPage[4004]{};
    char *endBuffer = bufferPage;
    memcpy(endBuffer, &page.id, sizeof(unsigned int));
    endBuffer += sizeof(unsigned int);
    for (int i = 0; i < 16; i++) {
        memcpy(endBuffer, &page.registro[i].id, sizeof(long long));
        endBuffer += sizeof(long long);
        memcpy(endBuffer, &page.registro[i].chaveBusca, sizeof(long long));
        endBuffer += sizeof(long long);
        memcpy(endBuffer, &page.registro[i].extra, sizeof(page.registro->extra));
        endBuffer += sizeof(page.registro->extra);
    }
    const unsigned int offset = page.id * sizeof(bufferPage);
    pageManager.seekp(offset, std::ios_base::beg);
    this->pageManager.write(bufferPage, sizeof(bufferPage));
}

Page PageManager::readPage(const unsigned int id) {
    char bufferPage[4000]{};
    const char *endBuffer = bufferPage;
    const unsigned int offset = id * 4004;
    Page page{};
    pageManager.seekg(offset,std::ios_base::beg);
    pageManager.read(reinterpret_cast<char *>(&page.id), sizeof(unsigned int));
    if(pageManager.eof()) {
        std::cerr << "Failed read page " << id << std::endl;
        throw std::runtime_error("Failed read page " + std::to_string(id));
    }
    pageManager.read(bufferPage, sizeof(bufferPage));
    for (int i = 0; i < 16; i++) {
        memcpy(&page.registro[i].id, endBuffer, sizeof(long long));
        endBuffer += sizeof(long long);
        memcpy(&page.registro[i].chaveBusca, endBuffer, sizeof(long long));
        endBuffer += sizeof(long long);
        memcpy(&page.registro[i].extra, endBuffer, sizeof(page.registro->extra));
        endBuffer += sizeof(page.registro->extra);
    }
    return page;
}

void PageManager::readAllPages(Registro &registro) {
  /*  try {
        while (this->fin.read(reinterpret_cast<char *>(&registro), sizeof(registro))) {
            std::cout << registro.id << std::endl;
            std::cout << registro.chaveBusca << std::endl;
            std::cout << registro.extra << std::endl;
        }
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }*/
}





