#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    for (uint32_t n, k; cin >> n >> k; ) {
        k = min(k, n - k);
        double e = 0;
        for (uint32_t d = 1; d <= k; ++d, n--)
            e += log10(n) - log10(d);
        cout << ((int)floor(e) + 1) << endl;
    }

    return 0;
}
