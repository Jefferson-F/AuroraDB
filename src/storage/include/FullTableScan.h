//
// Created by T.I on 18/11/2025.
//

#include "Page.h"

class FullTableScan {
private:

    public:
    explicit FullTableScan();

    static Page* locate(long long id);
    ~FullTableScan() = default;
};

