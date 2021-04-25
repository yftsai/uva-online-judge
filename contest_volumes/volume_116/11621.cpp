// #easy
#include <iostream>
#include <algorithm>
using namespace std;

// ceil(log2(m))
int16_t clog2(uint32_t m)
{
    int16_t e = 0, a = 0;
    for (; m > 1; m /= 2, e++)
        a = (m % 2 == 0) ? a : 1;
    return e + a;
}

uint64_t pow2(int16_t e)
{
    uint64_t v = 1, b = 2;
    for (; e > 0; e /= 2, b = b * b)
        v *= (e % 2 == 0) ? 1 : b;
    return v;
}

int main()
{
    for (uint32_t m; cin >> m && m != 0; ) {
        auto e = clog2(m);
        auto n = pow2(e);
        auto min_n = n;

        for (; e > 0; e--) {
            n /= 2;
            while (n < m)
                n *= 3;
            min_n = min(n, min_n);
        }
        cout << min_n << endl;
    }
    return 0;
}
