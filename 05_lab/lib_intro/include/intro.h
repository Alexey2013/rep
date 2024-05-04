#ifndef _INTRO_H
#define _INTRO_H
#include "polynom.h"
#include "SortedTable.h"
#include "ArrayHashTable.h"
using namespace std;

class Tables {
private:
    ScanTable<TPolynom, string > scanTable;
    SortedTable<TPolynom, string> sortedTable;
    ArrayHashTable<int, TPolynom> arrayHashTable;


    void Remove();
    void Remove_one();
    void poly_ops();
    int choose_table();
    void add();
    void add_one();
public:
    Tables()
        : scanTable(10),
        sortedTable(10),
        arrayHashTable(10,1) {
    }
  void menu();
};

int Tables::choose_table() {
    int choice;
    cout << "1)Scan Table" << endl;
    cout << "2)Sorted Table" << endl;
    cout << "3)Array Hash Table" << endl;
    cout << "0)CANCEL" << endl;
    cin >> choice;
    return choice;
}

void Tables::add_one() {
    TPolynom polynom;
    cout << "Enter polynom:" << endl;
    cin >> polynom;
    switch (choose_table()) {
    case 0:return;
    case 1: {
        scanTable.Insert(polynom, new std::string(polynom.ToString()));
        break;
    }
    case 2: {
        sortedTable.Insert(polynom, new std::string(polynom.ToString()));
        break;
    }
    case 3: {
        break;
    }
    }
}

void Tables::add() {
    int choice;
    TPolynom polynom; 
    cin >> polynom;
    cout << "1. Add to one table" << endl;
    cout << "2. Add to all tables" << endl;
    cout << "0. CANCEL" << endl;
    cin >> choice;
    switch (choice) {
    case 0:return;
    case 1: { add_one(); break; }
    case 2: { 
        scanTable.Insert(polynom, new std::string(polynom.ToString()));
        sortedTable.Insert(polynom, new std::string(polynom.ToString()));
        break; 
    }
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void Tables::Remove() {
    int choice;
    TPolynom polynom;
    cin >> polynom;
    cout << "1. Remove from one table" << endl;
    cout << "2. Remove from all tables" << endl;
    cout << "0. CANCEL" << endl;
    cin >> choice;
    switch (choice) {
    case 0:return;
    case 1: { Remove_one(); break; }
    case 2: {
        break;
    }
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}

void Tables::menu() {
	int choice;
do {
    cout << "Menu:" << endl;
    cout << "1. Add" << endl;
    cout << "2. Remove" << endl;
    cout << "3. See one table" << endl;
    cout << "4. See all tables" << endl;
    cout << "5. Polynoms" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 0: break;
    case 1: { add(); break; }
    case 2: { Remove(); break; }
    case 3: {
        switch (choose_table()) {
        case 0:return;
        case 1: {
            cout << scanTable;
            break;
        }
        case 2: {
            cout << sortedTable;
            break;
        }
        case 3: {
            cout << arrayHashTable;
            break;
        }
        }
        break;
    }
    case 4: { 
        cout << scanTable;
        cout << sortedTable;
        cout << arrayHashTable;
        break;
    }
    case 5: { poly_ops(); break; }
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
} while (choice != 0);    
}

#endif 