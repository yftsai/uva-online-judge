// #binary_search
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

uint32_t count_ap(const vector<uint32_t> &houses, const double d)
{
    uint32_t count = 0;
    for (size_t i = 0, j; i < houses.size(); i = j, count++)
        for (j = i + 1; j < houses.size() && houses[j] <= houses[i] + 2 * d; j++)
            ;
    return count;
}

double approximate(double d)
{
    return round(d * 10) / 10;
}

int main()
{
    uint32_t test_count, m, n;
    vector<uint32_t> houses;

    cout.precision(1);
    cout.setf(ios::fixed);

    for (cin >> test_count; test_count > 0 && cin >> n >> m; test_count--) {
        houses.resize(m);
        for (auto &h: houses)
            cin >> h;
        sort(houses.begin(), houses.end());

        double lower_d = 0, upper_d = (houses.back() - houses.front()) / 2.0 / n;
        while (approximate(lower_d) != approximate(upper_d)) {
            const double d = (lower_d + upper_d) / 2;
            if (count_ap(houses, d) <= n)
                upper_d = d;
            else
                lower_d = d;
        }

        cout << approximate(lower_d) << endl;
    }

    return 0;
}
