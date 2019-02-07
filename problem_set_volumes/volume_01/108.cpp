// #dynamic_programming
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int16_t col_sums[100][100], n;
    cin >> n;
    for (uint16_t i = 0; i < n && cin >> col_sums[i][0]; ++i)
        for (uint16_t j = 1; j < n && cin >> col_sums[i][j]; ++j)
            col_sums[i][j] += col_sums[i][j - 1u];

    int max_sum = col_sums[0][0];
    for (uint16_t lower_col = 0; lower_col < n; ++lower_col)
        for (uint16_t upper_col = lower_col; upper_col < n; ++upper_col) {
            int s = 0;
            for (uint16_t row = 0; row < n; ++row) {
                s += col_sums[row][upper_col] - ((lower_col == 0) ? 0 : col_sums[row][lower_col - 1u]);
                max_sum = max(max_sum, s);
                s = max(s, 0);
            }
        }
    cout << max_sum << endl;

    return 0;
}
