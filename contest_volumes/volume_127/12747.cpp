// #longest_increasing_sequence
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<uint32_t> indexes, last_idxes;
    uint16_t t;
    uint32_t n;
    cin >> t;
    for (uint16_t ncase = 1; ncase <= t && cin >> n; ncase++) {
        indexes.resize(n);
        for (uint32_t i = 0, j; i < n && cin >> j; i++)
            indexes[j - 1] = i;

        last_idxes.clear();
        for (uint32_t i = 0, j; i < n && cin >> j; i++) {
            auto k = indexes[j - 1];
            auto it = upper_bound(last_idxes.begin(), last_idxes.end(), k);
            if (it == last_idxes.end())
                last_idxes.push_back(k);
            else
                *it = k;
        }

        cout << "Case " << ncase << ": " << (n - last_idxes.size()) * 2 << endl;
    }

    return 0;
}
