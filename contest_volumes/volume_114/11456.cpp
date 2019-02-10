// #longest_increasing_subsequence
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    vector<uint32_t> weights, lis, lds;

    uint32_t test_count, n;
    for (cin >> test_count; test_count > 0 && cin >> n; --test_count, lis.clear(), lds.clear()) {
        weights.resize(n);
        for (auto &w: weights)
            cin >> w;

        uint16_t length = 0;
        for (auto wit = weights.rbegin(); wit != weights.rend(); ++wit) {
            auto it = lower_bound(lis.begin(), lis.end(), *wit, greater<uint32_t>());
            uint16_t len = it - lis.begin() + 1u;
            if (it == lis.end())
                lis.push_back(*wit);
            else
                *it = *wit;

            it = lower_bound(lds.begin(), lds.end(), *wit);
            len += it - lds.begin();
            if (it == lds.end())
                lds.push_back(*wit);
            else
                *it = *wit;

            length = max(length, len);
        }

        cout << length << endl;
    }
    return 0;
}
