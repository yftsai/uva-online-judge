// #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> potencies;
    for (uint16_t n; cin >> n; ) {
        potencies.assign(1u << n, 0);
        for (uint16_t corner = 0, weight; corner < potencies.size() && cin >> weight; ++corner)
            for (uint16_t i = 0, mask = 1u; i < n; ++i, mask <<= 1)
                potencies[corner ^ mask] += weight;

        uint32_t sum = 0;
        for (uint16_t corner = 0; corner < potencies.size(); ++corner)
            for (uint16_t i = 0, mask = 1u; i < n; ++i, mask <<= 1)
                if ((corner & mask) == 0)
                    sum = max<uint32_t>(sum, potencies[corner] + potencies[corner | mask]);
        cout << sum << endl;
    }

    return 0;
}
