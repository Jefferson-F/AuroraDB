#include <iostream>

#include "src/storage/include/FullTableScan.h"
#include "src/storage/include/PageManager.h"
#include "src/storage/include/Page.h"


int main() {

    constexpr char fileName[10] = "aurora.db";
    const Page *page = nullptr;
    PageManager pageManager(fileName);
    page = FullTableScan::locate(17);
    const Page pagina2 = pageManager.readPage(3);
    std::cout << page->id << std::endl;
    std::cout << pagina2.id << std::endl;

}