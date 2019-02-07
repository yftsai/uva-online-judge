#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> one_rows, three_rows;
    vector<vector<int>> one_cols, three_cols;
    string row;
    for (uint16_t m; cin >> m; one_rows.clear(), one_cols.clear(), three_rows.clear(), three_cols.clear()) {
        for (uint16_t r = 0; r < m && cin >> row; ++r)
            for (uint16_t c = 0; c < m; ++c)
                if (row[c] == '1') {
                    if (one_rows.size() == 0 || one_rows.back() != r) {
                        one_rows.push_back(r);
                        one_cols.emplace_back();
                    }
                    one_cols.back().push_back(c);
                }
                else if (row[c] == '3') {
                    if (three_rows.size() == 0 || three_rows.back() != r) {
                        three_rows.push_back(r);
                        three_cols.emplace_back();
                    }
                    three_cols.back().push_back(c);
                }

        int max_d = 0;
        for (uint16_t one_i = 0, three_i = 0; one_i < one_rows.size(); ++one_i) {
            auto one_row = one_rows[one_i];
            for (; three_i < three_rows.size() && three_rows[three_i] <= one_row; ++three_i)
                ;
            for (auto one_col: one_cols[one_i]) {
                int d = m * 2;
                for (uint16_t three_j = three_i; three_j > 0 && one_row < three_rows[three_j - 1u] + d && d > max_d; --three_j) {
                    const auto &cols = three_cols[three_j - 1];
                    auto it = lower_bound(cols.begin(), cols.end(), one_col);
                    if (it != cols.end())
                        d = min(d, one_row - three_rows[three_j - 1] + *it - one_col);
                    if (it != cols.begin())
                        d = min(d, one_row - three_rows[three_j - 1] + one_col - *(--it));
                }
                for (uint16_t three_j = three_i; three_j < three_rows.size() && three_rows[three_j] < one_row + d && d > max_d; ++three_j) {
                    const auto &cols = three_cols[three_j];
                    auto it = lower_bound(cols.begin(), cols.end(), one_col);
                    if (it != cols.end())
                        d = min(d, three_rows[three_j] - one_row + *it - one_col);
                    if (it != cols.begin())
                        d = min(d, three_rows[three_j] - one_row + one_col - *(--it));
                }
                max_d = max(max_d, d);
            }
        }
        cout << max_d << endl;
    }

    return 0;
}
