//
// Created by Jefferson on 22/08/2025.
//

#ifndef AURORADB_PAGEMANAGER_H
#define AURORADB_PAGEMANAGER_H
#include <fstream>

#include "Page.h"

class PageManager {
    private:
        std::fstream pageManager;
    public:
        explicit PageManager(const char *filename);
        ~PageManager() = default;
        void writePage(const Page &page);
        Page readPage(unsigned int id);
        void readAllPages(Registro &registro);
    };

#endif //AURORADB_PAGEMANAGER_H
