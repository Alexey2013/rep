//#include "intro.h"
#include "polynom.h"
#include "SortedTable.h"
#include "ArrayHashTable.h"

int main() {
	try {
		/*Tables example;
		example.menu();*/
		SortedTable<int, string> table(4);

		int key2 = 2;
		string data2 = "Data2";
		table.Insert(key2, new std::string(data2));

		int key1 = 1;
		string data1 = "Data1";
		table.Insert(key1, new std::string(data1));

		cout << table;

	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}
