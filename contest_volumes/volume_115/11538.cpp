// #combinatorics
#include <iostream>
#include <algorithm>
using namespace std;

int64_t count_diagonal_attacks(int32_t m, int32_t n)
{
    if (m > n)
        swap(m, n);

    const int64_t v = (m <= 2) ? 0 : int64_t(m - 2) * (m - 1);
    const int32_t w = (2 * m - 3);
    return int64_t(m) * (m - 1) * (n - m + 1)
        + v
        + ((w % 3 == 0) ? (w / 3 * v) : (v / 3 * w));
}

int main()
{
    for (uint32_t m, n; cin >> m >> n && m > 0; )
        cout << (int64_t(m) * n * (m + n - 2) + 2 * count_diagonal_attacks(m, n)) << endl;

    return 0;
}
