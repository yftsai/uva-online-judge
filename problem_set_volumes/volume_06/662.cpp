// #dynamic_programming
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

typedef pair<uint32_t, uint16_t> value_t;
typedef vector<vector<vector<value_t>>> table_t;
constexpr uint32_t UNKNOWN = numeric_limits<uint32_t>::max();

void ensure(table_t &sums, uint16_t k, uint16_t i, uint16_t j)
{
    if (k >= sums.size())
        sums.resize(k + 1);
    if (i >= sums[k].size())
        sums[k].resize(i + 1);
    if (j >= sums[k][i].size())
        sums[k][i].resize(j + 1, value_t(UNKNOWN, 0));
}

value_t minimize(const vector<int> &ds, uint16_t k, uint16_t i, uint16_t j, table_t &sums)
{
    ensure(sums, k, i, ds.size());
    if (sums[k][i][j].first != UNKNOWN)
        return sums[k][i][j];
    else {
        uint16_t g = (k + 1) / 2;
        uint16_t h = k - g;
        value_t result(numeric_limits<decltype(value_t::first)>::max(), 0);
        for (uint16_t m = i + g; m + h <= j; m++) {
            value_t left  = minimize(ds, g, i, m, sums);
            value_t right = minimize(ds, h, m, j, sums);
            result = min(value_t(left.first + right.first, m), result);
        }
        sums[k][i][j] = result;
        return result;
    }
}

void print(const vector<int> &ds, uint16_t k, uint16_t i, uint16_t j, uint16_t d, const table_t &sums)
{
    auto &v = sums[k][i][j];
    if (k == 1) {
        cout << "Depot " << d << " at restaurant "
             << (v.second + 1) << " serves ";
        if (j - i == 1)
            cout << "restaurant " << j << endl;
        else
            cout << "restaurants " << (i + 1) << " to " << j << endl;
    }
    else {
        uint16_t h = (k + 1) / 2;
        print(ds,     h,        i, v.second,     d, sums);
        print(ds, k - h, v.second,        j, d + h, sums);
    }
}

int main()
{
    vector<int> ds;
    table_t sums;
    uint32_t nchain = 1;

    for (uint16_t n, k; cin >> n >> k && n != 0; nchain++) {
        ds.resize(n);
        for (auto &d: ds)
            cin >> d;

        sums.clear();

        // initialize ranges with k == 1
        for (uint16_t i = 0; i < ds.size(); i++) {
            uint32_t s = 0;
            ensure(sums, 1, i, ds.size());
            sums[1][i][i + 1] = value_t(0, i);    // the trivial [i, i + 1)

            for (uint16_t m = i, j = i + 2; j <= ds.size(); j++) {
                s += ds[j - 1] - ds[m];
                while (m + 1 < j && (ds[m + 1] - ds[m]) * (m + 1 - i) < (ds[m + 1] - ds[m]) * (j - m - 1)) {
                    s -= (ds[m + 1] - ds[m]) * (j - m - 1) - (ds[m + 1] - ds[m]) * (m + 1 - i);
                    m++;
                }
                sums[1][i][j] = value_t(s, m);
            }
        }

        auto sum = minimize(ds, k, 0, ds.size(), sums).first;
        cout << "Chain " << nchain << endl;
        print(ds, k, 0, ds.size(), 1, sums);
        cout << "Total distance sum = " << sum << endl;
        cout << endl;
    }

    return 0;
}
