// #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    const uint16_t invalid_count = 1u << 15;
    vector<uint16_t> counts;

    uint32_t test_count;
    for (cin >> test_count; test_count > 0; --test_count) {
        uint16_t price, n;
        cin >> price >> n;
        counts.assign(1, 0);
        for (uint16_t i = 0, v; i < n && cin >> v; ++i) {
            counts.resize(counts.size() + v, invalid_count);
            for (uint16_t j = counts.size() - v; j > 0; --j)
                if (counts[j - 1u] != invalid_count) {
                    uint16_t &c = counts[j - 1u + v];
                    c = (c == invalid_count) ? (counts[j - 1u] + 1) : min<uint16_t>(c, counts[j - 1u] + 1u);
                }
            if (counts.size() >= price + 1u) {
                auto it = find_if(counts.begin() + price, counts.end(), [](uint16_t c) { return c != invalid_count; });
                if (it != counts.end())
                    counts.erase(++it, counts.end());
            }
        }
        cout << (counts.size() - 1u) << " " << counts.back() << endl;
    }

    return 0;
}
