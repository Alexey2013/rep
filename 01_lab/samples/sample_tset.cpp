#include <iostream>
#include "tset.h"
//const int n=5;
using namespace std;

void set() {
    int n;
    cout << "Enter n:" << endl;;
    cin >> n;
    TBitField bf1(n);
    TSet s1(n);
    TSet s2(n+1);
    cout << "Enter s1:" << endl;
    cin >> s1;
    cout << "1:" << s1 << endl;
    cout << "Enter s2:" << endl;
    cin >> s2;
    cout << "2:" << s2 <<endl;
    cout << "1==2:" << (s1 == s2) << "\n" << endl;
    cout << "+:" << (s1 + s2) << endl;
    cout << "+(Element):" << (s1 + 0) << endl;
    cout << "-(Element):" << (s1 - 1) << endl;
    cout << "*:" << (s1 * s2) << endl;
    cout << "~1:" << ~s1 << endl;
}

int main()
{
    try {set();}
    catch (string exp) {
        cout << exp << endl;
    }
}
