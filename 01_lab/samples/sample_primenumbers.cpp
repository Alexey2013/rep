#include <iomanip>

#ifndef USE_SET /

#include "tbitfield.h"

int main()
{
    int n, m, k, count;
    cout << "Input a number:";
    cin >> n;
    TBitField s(n + 1);
    for (m = 2; m <= n; m++)
        s.SetBit(m);
    for (m = 2; m * m <= n; m++)
        if (s.GetBit(m))
            for (k = 2 * m; k <= n; k += m)
                if (s.GetBit(k))
                    s.ClrBit(k);
    count = 0;
    k = 1;
    for (m = 2; m <= n; m++)
        if (s.GetBit(m))
        {
            count++;
            cout << setw(3) << m << " ";
            if (k++ % 10 == 0)
                cout << endl;
        }
    cout << endl;
    cout << "Count of prime digits: " << count << endl;
}
#else

#include "tset.h"

int main()
{
    int n, m, k, count;
    cout << "Input a number:";
    cin >> n;
    TSet s(n + 1);
    for (m = 2; m <= n; m++)
        s.InsElem(m);
    for (m = 2; m * m <= n; m++)
        if (s.IsMember(m))
            for (k = 2 * m; k <= n; k += m)
                if (s.IsMember(k))
    count = 0;
    k = 1;
    for (m = 2; m <= n; m++)
        if (s.IsMember(m))
        {
            count++;
            cout << setw(3) << m << " ";
            if (k++ % 10 == 0)
                cout << endl;
        }
    cout << endl;
    cout << "Count of prime digits: " << count << endl;
}

#endif
