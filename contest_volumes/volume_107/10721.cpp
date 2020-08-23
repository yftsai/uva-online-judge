// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    auto get_min_m = [](uint16_t n, uint16_t k) -> uint16_t {
        return (n + k - 1) / k;
    };
    vector<vector<uint64_t>> counts[50];    // BC(n, k, m) = counts[n - 1, k - 1, m - min_m(n, k)]

    for (uint16_t n = 1; n <= 50; ++n) {
        counts[n - 1].resize(n);

        counts[n - 1][0].resize(50 - get_min_m(n, 1) + 1, 1);   // k = 1
        for (uint16_t k = 2; k <= n; ++k)
            counts[n - 1][k - 1].resize(50 - get_min_m(n, k) + 1, 0);
    }

    for (uint16_t n = 1; n <= 50; ++n)
        for (uint16_t k = 1; k <= n; ++k) {
            const uint16_t min_m = get_min_m(n, k);
            for (uint16_t m = min_m; m <= 50; ++m)
                for (uint16_t last_width = 1; last_width <= m && n + last_width <= 50; ++last_width) {
                    auto &count = counts[n + last_width - 1][k][m - get_min_m(n + last_width, k + 1)];
                    count += counts[n - 1][k - 1][m - min_m];
                }
        }

    for (uint16_t n, k, m; cin >> n >> k >> m; ) {
        const uint16_t min_m = get_min_m(n, k);
        cout << ((k <= n && n <= m * k) ? counts[n - 1][k - 1][m - min_m] : 0) << endl;
    }

    return 0;
}
