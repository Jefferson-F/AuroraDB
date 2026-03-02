//
// Created by T.I on 30/08/2025.
//

#ifndef AURORADB_PAGE_H
#define AURORADB_PAGE_H
#include "Registro.h"

struct Page {
    unsigned int id;
    Registro registro[16];
};

#endif //AURORADB_PAGE_H