#include <iostream>
using namespace std;

int  main()
{
    int m[13];
    for (int k=1, nlive; k<14; ++k) {
        m[k-1] = k;
        do {
            ++m[k-1];
            nlive = 2*k;
            for (int p = (m[k-1]-1)%nlive; p>=k; p=(p+m[k-1]-1)%(--nlive))
                ;
        } while (nlive > k);
    }

    for (int k; cin >> k && k != 0;)
        cout << m[k-1] << endl;

    return 0;
}
