// #dynamic_programming
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t n;
    vector<vector<uint16_t>> coin_counts;
    for (cin >> n; n > 0; --n) {
        uint32_t m, s;
        cin >> m >> s;

        coin_counts.resize(s + 1u);
        for (uint16_t v = 0; v < coin_counts.size(); ++v)
            coin_counts[v].assign(ceil(sqrt(s * s - v * v)) + 1u, s + 1u);
        coin_counts[0][0] = 0;

        for (uint16_t v, w; m > 0 && cin >> v >> w; --m)
            if (v > 0 || w > 0)
                for (uint16_t i = 0; i + v < coin_counts.size(); ++i)
                    for (uint16_t j = 0; j + w < coin_counts[i + v].size(); ++j)
                        coin_counts[i + v][j + w] = min<uint16_t>(coin_counts[i + v][j + w],
                                                                  coin_counts[i][j] + 1u);

        uint16_t count = s + 1;
        for (uint32_t v = 0; v < coin_counts.size(); ++v) {
            uint32_t w = sqrt(s * s - v * v);
            if (w < coin_counts[v].size() && v * v + w * w == s * s)
                count = min(count, coin_counts[v][w]);
        }

        if (count <= s)
            cout << count << endl;
        else
            cout << "not possible" << endl;
    }
    return 0;
}
