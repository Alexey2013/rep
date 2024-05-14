#ifndef _INTRO_H
#define _INTRO_H
#include "polynom.h"
#include "SortedTable.h"
#include "ArrayHashTable.h"
using namespace std;

class Tables {
private:
    ScanTable<string, TPolynom > scanTable;
    SortedTable<string, TPolynom> sortedTable;
    PolynomialHashTable<string, TPolynom> arrayHashTable;

    void poly_ops();
    int choose_table();
    void remove(const string& str);
    void remove_one(const string& str);
    void add(const string& str);
    void add_one(const string& str);
    TabRecord<string, TPolynom>* find(const string& str);
public:
  Tables():scanTable(10),sortedTable(10), arrayHashTable(10,1) {}
  void menu();
};

int Tables::choose_table() {
    int choice;
    cout << "TABLES" << endl;
    cout << "1)Scan Table" << endl;
    cout << "2)Sorted Table" << endl;
    cout << "3)Array Hash Table" << endl;
    cout << "0)CANCEL" << endl;
    cout << "Enter:";
    if (!(cin >> choice)) {
        cout << "Invalid input." << endl;
        return 0; 
    }

    return choice;
}

void Tables::add_one(const string& str) {
    TPolynom* polynom = new TPolynom(str);
    switch (choose_table()) {
    case 0:return;
    case 1: {
        scanTable.Insert(str,polynom);
        break;
    }
    case 2: {
        sortedTable.Insert(str,polynom);
        break;
    }
    case 3: {
        arrayHashTable.Insert(str,polynom);
        break;
    }
    }
}

void Tables::add(const string& str) {
    int choice;
    cout << "1. Add to one table" << endl;
    cout << "2. Add to all tables" << endl;
    cout << "0. CANCEL" << endl;
    cout << "Enter:";
    cin >> choice;
    switch (choice) {
    case 0:return;
    case 1: { add_one(str); break; }
    case 2: {
        TPolynom* polynom = new TPolynom(str);
        scanTable.Insert(str, polynom);
        sortedTable.Insert(str, polynom);
        arrayHashTable.Insert(str, polynom);
        break; 
    }
    }
}

void Tables::remove_one(const string& str) {
    switch (choose_table()) {
    case 0:return;
    case 1: {
        scanTable.Remove(str);
        break;
    }
    case 2: {
        sortedTable.Remove(str);
        break;
    }
    case 3: {
        arrayHashTable.Remove(str);
        break;
    }
    }
}

void Tables::remove(const string& str) {
    int choice;
    cout << "1. Remove from one table" << endl;
    cout << "2. Remove from all tables" << endl;
    cout << "0. CANCEL" << endl;
    cout << "Enter:";
    cin >> choice;
    switch (choice) {
    case 0:return;
    case 1: { remove_one(str); break; }
    case 2: {
        scanTable.Remove(str);
        sortedTable.Remove(str);
        arrayHashTable.Remove(str);
        break;
    }
    }
}

void Tables::poly_ops() {
    string pol_name1, pol_name2;
    cout << "Enter first polynomial: ";
    cin >> pol_name1;

    TabRecord<string, TPolynom>* rec1 = find(pol_name1);
    if (rec1 != nullptr) {
        cout << "Enter second polynomial: ";
        cin >> pol_name2;

        TabRecord<string, TPolynom>* rec2 =find(pol_name2);
        if (rec2 != nullptr) {
            TPolynom p1 = *rec1->GetData();
            TPolynom p2 = *rec2->GetData();
            TPolynom p3;

            int choice;
            cout << "1)+" << endl;
            cout << "2)-" << endl;
            cout << "3)*" << endl;
            cout << "Enter:";
            cin >> choice;
            switch(choice){
            case 0:return;
            case 1: { p3 = p1 + p2; break; }
            case 2: { p3 = p1 - p2; break; }
            case 3: { p3 = p1 * p2; break; }
            }
            cout << p3;
            add(p3.ToString());
        }
    }
}

TabRecord<string, TPolynom>* Tables::find(const string& str) {
    TabRecord<string, TPolynom>* record = nullptr;

    if ((record = scanTable.Find(str)) != nullptr) {
        return record;
    }
    if ((record = sortedTable.Find(str)) != nullptr) {
        return record;
    }
    if ((record = arrayHashTable.Find(str)) != nullptr) {
        return record;
    }

    return nullptr;
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
    cout << "Enter your choice:";
    cin >> choice;
    switch (choice) {
    case 0: break;
    case 1: { 
        cout << "Enter polynom:";
        string pol_name;
        cin >> pol_name;
        add(pol_name); 
        break; 
    }
    case 2: { 
        cout << "Enter polynom:";
        string pol_name;
        cin >> pol_name;
        remove(pol_name); 
        break; 
    }
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
        cout << "ScanTable" << endl;
        cout << scanTable << endl;
        cout << "SortedTable" << endl;
        cout << sortedTable << endl;
        cout << "ArrayHashTable" << endl;
        cout << arrayHashTable << endl;
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