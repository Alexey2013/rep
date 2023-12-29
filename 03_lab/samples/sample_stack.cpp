#include "stack.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	try {
		int n;
		cout << "Enter n:";
		cin >> n;
		TStack<int> st(n);
		int answer, element;
		string elem;
		while (true) {
			cout << "1) Push()" << endl;
			cout << "2) Pop()" << endl;
			cout << "3) Top()" << endl;
			cout << "0) Exit\n" << endl;
			cout << "Enter:";
			cin >> answer;
			switch (answer) {
			case 1: {
				cout << "Enter element:";
				cin >> element;
				st.Push(element);
				break;
			}
			case 2: {
				cout <<"Pop:"<< st.Pop() << endl; break;
			}
			case 3: {
				cout << "Element on the top of stack: " << st.Top() << endl;
				break;
			}
			default: {
				return 0;
			}
			}
		}
	}
	catch (string exp) {
		cout << exp << endl;
	}

	
}