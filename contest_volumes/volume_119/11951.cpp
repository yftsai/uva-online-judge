// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

static int get_subrow_price(const vector<int> &price_sums, uint16_t lb, uint16_t ub)
{
    return price_sums[ub] - ((lb == 0) ? 0 : price_sums[lb - 1u]);
}

int main()
{
    uint16_t t, n, m;
    int k;
    vector<vector<int>> price_sums;
    cin >> t;
    for (uint16_t case_number = 1; case_number <= t && cin >> n >> m >> k; ++case_number) {
        price_sums.resize(n);
        for (auto &ps: price_sums) {
            ps.resize(m);
            for (uint16_t i = 0; i < m && cin >> ps[i]; ++i)
                if (i > 0)
                    ps[i] += ps[i - 1u];
        }

        uint16_t s = 0;
        int p = 0;
        for (uint16_t col_lb = 0; col_lb < m; ++col_lb)
            for (uint16_t col_ub = col_lb; col_ub < m; ++col_ub) {
                uint16_t row_lb = 0, area_sum = 0;
                int price_sum = 0;
                for (uint16_t row_ub = 0; row_ub < n; ++row_ub) {
                    price_sum += get_subrow_price(price_sums[row_ub], col_lb, col_ub);
                    area_sum += col_ub - col_lb + 1u;

                    for (; price_sum > k; price_sum -= get_subrow_price(price_sums[row_lb++], col_lb, col_ub))
                        area_sum -= col_ub - col_lb + 1u;
                    if (area_sum > s || (area_sum == s && price_sum < p)) {
                        s = area_sum;
                        p = price_sum;
                    }
                }
            }
        cout << "Case #" << case_number << ": " << s << " " << p << endl;
    }
    return 0;
}
