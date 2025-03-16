// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> weights;

    uint16_t t;
    cin >> t;
    for (uint16_t no = 1; no <= t; no++) {
        uint16_t n, p, q;
        cin >> n >> p >> q;

        weights.resize(n);
        for (auto &w: weights)
            cin >> w;
        sort(weights.begin(), weights.end());

        uint16_t total_weight = 0, count = 0;
        for (; count < n && count < p && total_weight + weights[count] <= q; count++)
            total_weight += weights[count];

        cout << "Case " << no << ": " << count << endl;
    }

    return 0;
}
