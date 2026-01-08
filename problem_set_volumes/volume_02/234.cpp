// #easy
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
using namespace std;

typedef pair<uint16_t, uint32_t> apoint_t;

void get_miss_times(const vector<apoint_t> &apoints,
                    vector<uint32_t> &times,
                    array<uint32_t, 5> &miss_times)
{
    miss_times.fill(0);

    for (auto &it: apoints) {
        auto t = it.second;
        uint16_t j = 0;
        while (j + 1u < times.size() && times[j + 1] <= t)
            j++;
        miss_times[it.first] += min(t - times[j],
                                    j + 1u < times.size() ? times[j + 1] - t : t - times[j]);
    }
}

int main()
{
    vector<uint32_t> order, times, best_order;
    vector<apoint_t> apoints;
    array<uint32_t, 5> miss_times, best_miss_times;

    times.push_back(0);

    uint16_t p, a;
    for (uint32_t no = 1; cin >> p && p > 0; no++) {
        order.resize(p);
        for (auto &len: order)
            cin >> len;

        cin >> a;
        apoints.resize(a);
        for (auto &it: apoints) {
            cin >> it.first >> it.second;
            it.first--;
        }

        best_miss_times.fill(numeric_limits<uint32_t>::max());
        sort(order.begin(), order.end());
        do {
            times.resize(1);
            for (auto len: order)
                times.push_back(times.back() + len);
            get_miss_times(apoints, times, miss_times);

            if (miss_times < best_miss_times) {
                best_order = order;
                best_miss_times = miss_times;
            }
        } while (next_permutation(order.begin(), order.end()));

        cout << "Data set " << no << endl;
        cout << "Order:";
        for (auto len: best_order)
            cout << " " << len;
        cout << endl;
        cout << "Error: " << accumulate(best_miss_times.begin(), best_miss_times.end(), 0) << endl;
    }

    return 0;
}
