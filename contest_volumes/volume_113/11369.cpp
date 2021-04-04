// #greedy #trivial
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    uint16_t t, n;
    vector<uint16_t> prices(20000);
    for (cin >> t; t > 0 && cin >> n; --t) {
        prices.resize(n);
        for (auto &p: prices)
            cin >> p;

        sort(prices.begin(), prices.end(), greater<uint16_t>());
        uint32_t discount = 0;
        for (uint16_t i = 2; i < n; i += 3)
            discount += prices[i];
        cout << discount << endl;
    }

    return 0;
}
