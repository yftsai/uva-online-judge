// #dynamic_programming
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t test_count, a, b, c;
    int64_t rectangle_sums[20][20][20];
    for (cin >> test_count; test_count > 0 && cin >> a >> b >> c; --test_count) {
        for (uint16_t i = 0; i < a; ++i)
            for (uint16_t j = 0; j < b; ++j) {
                for (uint16_t k = 0; k < c && cin >> rectangle_sums[i][j][k]; ++k) {
                    rectangle_sums[i][j][k] += (i == 0) ? 0 : rectangle_sums[i - 1u][j][k];
                    rectangle_sums[i][j][k] += (j == 0) ? 0 : rectangle_sums[i][j - 1u][k];
                    rectangle_sums[i][j][k] -= (i == 0 || j == 0) ? 0 : rectangle_sums[i - 1u][j - 1u][k];
                }
            }

        auto max_sum = numeric_limits<int64_t>::min();
        typedef pair<uint16_t, uint16_t> range;
        for (range i = range(0, 0); i.first < a; i.second = (i.second + 1u < a) ? (i.second + 1u) : (++i.first))
            for (range j = range(0, 0); j.first < b; j.second = (j.second + 1u < b) ? (j.second + 1u) : (++j.first)) {
                int64_t sum = 0;
                for (uint16_t k = 0; k < c; ++k, sum = (sum < 0) ? 0 : sum) {
                    sum += rectangle_sums[i.second][j.second][k];
                    sum -= (i.first == 0) ? 0 : rectangle_sums[i.first - 1u][j.second][k];
                    sum -= (j.first == 0) ? 0 : rectangle_sums[i.second][j.first - 1u][k];
                    sum += (i.first == 0 || j.first == 0) ? 0 : rectangle_sums[i.first - 1u][j.first - 1u][k];
                    max_sum = max(max_sum, sum);
                }
            }
        cout << max_sum << endl;
        if (test_count > 1u)
            cout << endl;
    }

    return 0;
}
