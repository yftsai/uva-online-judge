// #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<vector<int16_t>> col_accs;
    uint16_t test_count, n;
    for (cin >> test_count; test_count > 0 && cin >> n; --test_count) {
        col_accs.resize(n);
        for (auto &row: col_accs) {
            row.resize(n);
            for (uint16_t i = 0; i < row.size() && cin >> row[i]; ++i)
                row[i] += (i > 0) ? row[i - 1u] : 0;
        }

        int max_sum = col_accs[0][0];
        for (uint16_t lower_y = 0; lower_y < n; ++lower_y)
            for (uint16_t upper_y = lower_y; upper_y < lower_y + n; ++upper_y) {
                int sum = 0, min_sum = 0;
                int pos_sum = 0, neg_sum = 0;
                bool is_all_non_positive = true;
                for (uint16_t upper_x = 0; upper_x < n; ++upper_x, pos_sum = max(pos_sum, 0), neg_sum = min(neg_sum, 0)) {
                    const auto &accs = col_accs[upper_x % n];
                    int16_t s = ((upper_y < n) ? accs[upper_y] : (accs[n - 1u] + accs[upper_y % n]))
                                - ((lower_y == 0) ? 0 : accs[lower_y - 1u]);
                    sum += s;
                    pos_sum += s;
                    neg_sum += s;
                    is_all_non_positive = is_all_non_positive && (s <= 0);
                    max_sum = max(max_sum, pos_sum);
                    min_sum = min(min_sum, neg_sum);
                }
                max_sum = max(max_sum, is_all_non_positive ? max_sum : (sum - min_sum));
            }
        cout << max_sum << endl;
    }

    return 0;
}
