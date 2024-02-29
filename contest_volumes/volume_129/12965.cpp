// #easy
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    uint32_t n;
    uint16_t p, c;
    vector<uint32_t> pprices, cprices;

    for (cin >> n; n > 0 && cin >> p >> c; n--) {
        pprices.resize(p);
        for (auto &p: pprices)
            cin >> p;
        sort(pprices.begin(), pprices.end());

        cprices.resize(c);
        for (auto &p: cprices)
            cin >> p;
        sort(cprices.begin(), cprices.end());

        uint16_t angry_count = p;
        uint32_t price = 0;
        for (uint32_t i = 0; i < p; i++) {
            auto it = lower_bound(cprices.begin(), cprices.end(), pprices[i]);
            uint16_t a = p - i - 1 + (it - cprices.begin());
            if (a < angry_count || (a == angry_count && pprices[i] < price)) {
                angry_count = a;
                price = pprices[i];
            }
        }

        cout << price << " " << angry_count << endl;
    }
    return 0;
}
