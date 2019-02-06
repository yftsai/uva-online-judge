// #shortest_path
#include <iostream>
#include <memory>
#include <limits>
#include <numeric>
using namespace std;

int main()
{
    constexpr uint16_t n = 100;
    bool is_used[n];
    unique_ptr<uint16_t[]> distances[n];
    for (auto &ds: distances)
        ds.reset(new uint16_t[n]);

    uint32_t case_number = 1;
    cout.setf(ios::fixed);
    cout.precision(3);
    for (uint16_t a, b; cin >> a >> b && a > 0; ++case_number) {
        fill(is_used, is_used + n, false);
        for (auto &ds: distances)
            fill(ds.get(), ds.get() + n, n);
        do {
            is_used[a - 1u] = is_used[b - 1u] = true;
            distances[a - 1u][b - 1u] = 1u;
        } while (cin >> a >> b && a > 0);

        for (uint16_t m = 0; m < n; ++m)
            for (uint16_t i = 0; is_used[m] && i < n; ++i)
                for (uint16_t j = 0; is_used[i] && m != i && j < n; ++j)
                    if (is_used[j] && m != j && i != j)
                        distances[i][j] = min<uint16_t>(distances[i][j], distances[i][m] + distances[m][j]);

        uint32_t sum = 0;
        for (uint16_t i = 0; i < n; ++i)
            for (uint16_t j = i + 1u; is_used[i] && j < n; ++j)
                if (is_used[j] && i != j)
                    sum += distances[i][j] + distances[j][i];

        const uint16_t page_count = accumulate(is_used, is_used + n, 0u, [](uint16_t c, bool u) { return c + (u ? 1u : 0); });
        const uint16_t pair_count = page_count * (page_count - 1u);
        cout << "Case " << case_number << ": average length between pages = " << (double(sum) / pair_count) << " clicks" << endl;
    }

    return 0;
}
