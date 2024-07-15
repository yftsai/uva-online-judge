// #trivial
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;

int main()
{
    array<uint32_t, 21> specials = {
               1,       64,      729,     4096,    15625,
           46656,   117649,   262144,   531441,  1000000,
         1771561,  2985984,  4826809,  7529536, 11390625,
        16777216, 24137569, 34012224, 47045881, 64000000,
        85766121
    };

    for (uint32_t n; cin >> n && n > 0; ) {
        auto it = lower_bound(specials.begin(), specials.end(), n);
        cout << ((it != specials.end() && *it == n) ? "Special" : "Ordinary")
             << endl;
    }

    return 0;
}
