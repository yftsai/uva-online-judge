// #easy #sort
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main()
{
    vector<int32_t> profits;

    uint16_t t;
    uint32_t n, k;
    cin >> t;
    for (uint16_t cno = 1; cno <= t && cin >> n >> k; cno++) {
        profits.resize(n);
        for (auto &p: profits)
            cin >> p;
        for (auto &p: profits) {
            int32_t q;
            cin >> q;
            p = q - p;
        }

        sort(profits.begin(), profits.end());
        uint32_t b = k;
        while (b > 0 && profits[b - 1] > 0)
            b--;

        auto profit = accumulate<int32_t *, int64_t>(profits.data() + b, profits.data() + profits.size(), 0);
        cout << "Case " << cno << ": ";
        if (profit > 0)
            cout << profit << endl;
        else
            cout << "No Profit" << endl;
    }

    return 0;
}
