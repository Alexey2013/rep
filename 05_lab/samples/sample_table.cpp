#include <iostream>
#include "table.h"
#include "ScanTable.h"

int main() {
    try {
        ScanTable<std::string, int> scan_table(100);
        scan_table.Insert("a", new int(2));

        scan_table.Insert("a", new int(5));
        scan_table.Insert("a", new int(23));
    }
    catch (std::exception ex) {
        std::cout << ex.what();
    }

    return 0;
}