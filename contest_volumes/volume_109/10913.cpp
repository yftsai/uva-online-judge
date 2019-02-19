// #dynamic_programming
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    const int unreachable = numeric_limits<int>::min();
    vector<vector<int>> last_paths, current_paths;
    vector<int> row;
    auto count_negative = [](int v) -> uint16_t { return (v < 0) ? 1 : 0; };

    uint32_t case_number = 1;
    for (uint16_t n, k; cin >> n >> k && n > 0; ++case_number) {
        last_paths.resize(n);
        current_paths.resize(n);
        for (uint16_t c = 0; c < n; ++c) {
            last_paths[c].assign(k + 1u, unreachable);
            current_paths[c].resize(k + 1u);
        }
        last_paths[0][0] = 0;

        row.resize(n);
        for (uint16_t r = 0; r < n; ++r, last_paths.swap(current_paths)) {
            for (auto &v: row)
                cin >> v;
            for (auto &ps: current_paths)
                ps.assign(k + 1u, unreachable);

            for (uint16_t c = 0; c < n; ++c)
                for (uint16_t j = 0; j <= k; ++j) {
                    const uint16_t i = j + count_negative(row[c]);
                    if (last_paths[c][j] != unreachable && i <= k) {
                        const int s = last_paths[c][j] + row[c];
                        current_paths[c][i] = max(current_paths[c][i], s);

                        int t = s;
                        for (uint16_t d = c, h = i; d > 0 && (h += count_negative(row[d - 1u])) <= k; --d)
                            current_paths[d - 1u][h] = max(current_paths[d - 1u][h], t += row[d - 1u]);
                        t = s;
                        for (uint16_t d = c + 1u, h = i; d < n && (h += count_negative(row[d])) <= k; ++d)
                            current_paths[d][h] = max(current_paths[d][h], t += row[d]);
                    }
                }
        }

        int sum = *max_element(last_paths.back().begin(), last_paths.back().end());
        cout << "Case " << case_number << ": ";
        if (sum == unreachable)
            cout << "impossible" << endl;
        else
            cout << sum << endl;
    }
    return 0;
}
