#include "matrix.h"
#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter matrix dimension:";
    cin >> n;
    TMatrix <double> m1(n), m2(n), m3(n);
    cin >> m1;
    cin >> m2;
cout << "1:" <<endl << m1 <<endl;
cout << "2:" << endl <<m2<< endl;
cout << "1+ 2:" << endl << m1+m2 <<endl;
cout << "1- 2:" << endl << m1 - m2 << endl;
cout << "1*2:" <<endl << m1* m2 << endl;
m1 = m2;
cout << "1:" << endl << m1 << endl;
cout << "1==2:" <<( m1== m2);
    return 0;
}