//
// Created by T.I on 18/11/2025.
//
#include "include/Page.h"
#include "include/FullTableScan.h"

#include <iostream>

#include "include/BufferPoolManager.h"

FullTableScan::FullTableScan() = default;


Page *FullTableScan::locate(const long long id) {
    unsigned int idPage = 0;
    const auto bufferPoolManager = new BufferPoolManager();
    Page *page = nullptr;
    while (true) {
        idPage++;
        page = bufferPoolManager->pin(idPage);
        if (page == nullptr) {
            std::cerr << "erro: Registro não localizado";
            return nullptr;
        }
        for (const auto & i : page->registro) {
            if (i.id == id) {
                return page;
            }
        bufferPoolManager->unpin(idPage);


        }





    }
}
