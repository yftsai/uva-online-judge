// #dynamic_programming
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<vector<uint16_t>> weights;
    for (string s; cin >> s && s != "*"; ) {
        weights.assign(s.size(), vector<uint16_t>());
        weights[0].resize(s.size(), 1u);

        for (uint16_t len = 2; len <= s.size(); ++len) {
            weights[len - 1u].resize(s.size() - len + 1u, len);

            for (uint16_t begin = 0; begin + len <= s.size(); ++begin) {
                auto &w = weights[len - 1u][begin];
                for (uint16_t flen = 1; flen < len; ++flen) {
                    w = min<uint16_t>(w, weights[flen - 1u][begin] + weights[len - flen - 1u][begin + flen]);

                    for (uint16_t p = begin + flen;
                         p + flen <= begin + len && equal(s.begin() + begin, s.begin() + begin + flen, s.begin() + p);
                         p += flen) {
                            uint16_t rlen = begin + len - p - flen;
                            w = min<uint16_t>(w, weights[flen - 1u][begin] + ((rlen == 0) ? 0 : weights[rlen - 1u][p + flen]));
                        }
                }
            }
        }
        cout << weights[s.size() - 1u][0] << endl;
    }

    return 0;
}
