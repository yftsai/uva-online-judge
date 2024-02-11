// #easy_input
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t t, a;
    uint32_t n, q, x;
    vector<bool> mask(256);
    vector<uint32_t> xs(256);

    for (cin >> t; t > 0 && cin >> n >> q; t--) {
        mask.clear();
        mask.resize(256, false);
        for (uint32_t i = 0; i < n && cin >> x; i++)
            mask[x % mask.size()] = true;

        xs.clear();
        for (uint16_t i = 0; i < mask.size(); i++)
            if (mask[i])
                xs.push_back(i);

        for (uint32_t i = 0; i < q && cin >> a; i++) {
            uint16_t result = 0;
            for (auto x: xs)
                result = max(uint16_t(a & x), result);
            cout << result << endl;
        }
    }

    return 0;
}
