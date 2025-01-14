// #dynamic_programming
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main()
{
    vector<vector<uint16_t>> freqs;
    vector<vector<uint32_t>> costs;
    for (uint16_t n; cin >> n; ) {
        freqs.resize(n + 1);
        costs.resize(n + 1);
        for (uint16_t i = 0; i < n; i++) {
            freqs[i].resize(2);
            freqs[i][0] = 0;
            cin >> freqs[i][1];
            costs[i].resize(2, 0);
        }
        freqs.back().resize(1, 0);
        costs.back().resize(1, 0);

        for (uint16_t len = 2; len <= n; len++) {
            for (uint16_t i = 0; i + len <= n; i++) {
                freqs[i].push_back(freqs[i].back() + freqs[i + len - 1][1]);

                auto cost = numeric_limits<uint32_t>::max();
                for (uint16_t j = i; j < i + len; j++) {
                    uint16_t rlen = i + len - j - 1;
                    uint32_t c = costs[i][j - i]    + freqs[i][j - i]
                               + costs[j + 1][rlen] + freqs[j + 1][rlen];
                    if (c < cost)
                        cost = c;
                }
                costs[i].push_back(cost);
            }
        }
        cout << costs[0][n] << endl;
    }
    return 0;
}
