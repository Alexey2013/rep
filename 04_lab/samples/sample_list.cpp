#include "list.h"
#include <iostream>
using namespace std;

int main() {
    TList<int> myList;
    myList.insert_first(3);
    myList.insert_first(2);
    myList.insert_first(1);
    myList.print();
    myList.remove(3);
     myList.print();
    return 0;
}
