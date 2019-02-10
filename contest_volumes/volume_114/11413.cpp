// #easy
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
    vector<uint32_t> capacities;
    for (uint32_t n, m; cin >> n >> m; ) {
        capacities.resize(n);
        for (auto &c: capacities)
            cin >> c;

        uint32_t min_capacity = *max_element(capacities.begin(), capacities.end());
        uint32_t max_capacity = accumulate(capacities.begin(), capacities.end(), 0);
        while (min_capacity < max_capacity) {
            uint32_t mid_capacity = (min_capacity + max_capacity) / 2;
            bool is_milk_remained = true;
            for (uint32_t i = 0, j = 0; (is_milk_remained = (i < n)) && j < m; ++j)
                for (uint32_t c = mid_capacity; i < n && capacities[i] <= c; ++i)
                    c -= capacities[i];

            if (is_milk_remained)
                min_capacity = mid_capacity + 1u;
            else
                max_capacity = mid_capacity;
        }
        cout << min_capacity << endl;
    }
    return 0;
}
