#include <iostream>
#include "vector.h"

int main()
{
	int n;
	cout << "Enter the vector dimension:";
	cin >> n;
	TVector<int> v1(n), v2(n);
	cout << "Input the first vector:" << endl;;
	cin >> v1;
	cout << "Input the second vector:" << endl;;
	cin >> v2;
	cout << "v1:" << v1 << endl;
	cout << "v2:" << v2 << endl;
	cout << "v1+v2:" <<v1 + v2 << endl;
	cout << "v1-v2:" << v1 - v2 << endl;
	cout << "v1*v2:" << v1 * v2 << endl;
	cout << "v1+5: " << v1 - 2 << endl;
	cout << "v2-10: " << v2 + 2 << endl;
	cout << "Size:" << v1.GetSize() << endl;
	v1 = v2;
	cout << "v1:" << v1 << endl;
	cout << "v1==v2:" << (v1 == v2) << endl;
	return 0;
}
