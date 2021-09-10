// #easy #dynamic_programming
#include <iostream>
#include <array>
#include <vector>
using namespace std;

int main()
{
    array<uint16_t, 8> factorials = {
        1, 2, 6, 24, 120,
        720, 5040, 40320
    };

    vector<uint32_t> ks(1000 * 100 + 1);
    ks[0] = 0;
    for (uint32_t n = 1; n < ks.size(); n++) {
        ks[n] = n;
        for (const auto f: factorials)
            if (n >= f)
                ks[n] = min(ks[n], ks[n - f] + 1);
    }

    for (uint32_t n; cin >> n; )
        cout << ks[n] << endl;

    return 0;
}
