// #common_greatest_divisor
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

uint32_t gcd(uint32_t a, uint32_t b)
{
    while ((a %= b) != 0)
        swap(a, b);
    return b;
}

template<size_t COUNT>
void optimize_height(
    const vector<uint32_t> &coin_ts,
    const uint32_t height,
    uint32_t h,
    uint32_t *lb,
    uint32_t *ub,
    uint16_t index = 0)
{
        for (; index < coin_ts.size(); ++index) {
            uint32_t m = h / gcd(h, coin_ts[index]) * coin_ts[index];
            optimize_height<COUNT + 1>(
                coin_ts,
                height,
                m,
                lb,
                ub,
                index + 1);
        }
}

template<>
void optimize_height<4>(
    const vector<uint32_t> &,
    const uint32_t height,
    uint32_t h,
    uint32_t *lb,
    uint32_t *ub,
    uint16_t)
{
    *lb = max(*lb, height / h * h);
    *ub = min(*ub, (height + h - 1) / h * h);
}

int main()
{
    vector<uint32_t> coin_ts;
    for (uint16_t n, t; cin >> n >> t && n > 0; ) {
        coin_ts.resize(n);
        for (auto &t: coin_ts)
            cin >> t;

        for (uint32_t i = 0, height; i < t && cin >> height; ++i) {
            uint32_t lb = 0, ub = numeric_limits<uint32_t>::max();
            constexpr uint32_t init_height = 1;
            optimize_height<0>(
                coin_ts,
                height,
                init_height,
                &lb,
                &ub);
            cout << lb << " " << ub << endl;
        }
    }

    return 0;
}
