#include "tbitfield.h"

void bitfield()
{
	cout << "Enter n:";
	int n;
	cin >> n;
	TBitField bf1(n);
	TBitField bf2(n+1);
	cout << "Enter bf1(n):" << endl;;
	cin >> bf1;
	cout << "1:" << bf1 << endl;
	cout << "Enter bf2(n+1):" << endl;;
	cin>>bf2;
	cout << "2:" << bf2 << endl;
	bf2.ClrBit(1);
	cout << "2:" << bf2 << endl;
	cout << "1&2:" << (bf1 & bf2) << endl;
	cout << "1|2:" << (bf1 | bf2) << endl;
	cout << "1==2:" << (bf1 == bf2) << endl;
	cout << "~1:" << (~bf1) << endl;
	cout << "Bitfield length(bf1): " << bf1.GetLength() << endl;
}

int main()
{
	try {
		bitfield();
	}
	catch (string exp) {
		cout << exp << endl;
	}
}
