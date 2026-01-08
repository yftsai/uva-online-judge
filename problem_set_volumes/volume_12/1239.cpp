// #dynamic_programming
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    uint32_t t, k;
    string s;
    vector<uint16_t> ks;

    for (cin >> t; t > 0 && cin >> s >> k; t--) {
        ks.resize(s.size());
        uint16_t max_length = k;
        for (uint16_t i = s.size(); i > 0; i--) {
            uint16_t b = i - 1;
            for (uint16_t len = s.size() - b; len > 0; len--) {
                ks[b + len - 1] = (s[b] == s[b + len - 1] ? 0 : 1)
                                + (len <= 2 ? 0 : ks[b + len - 2]);

                if (ks[b + len - 1] <= k)
                    max_length = max(len, max_length);
            }
        }

        cout << max_length << endl;
    }

    return 0;
}
