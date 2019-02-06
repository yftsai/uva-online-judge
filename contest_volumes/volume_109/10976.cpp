// #trivial
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<pair<uint32_t, uint32_t>> xys;
    for (uint32_t k; cin >> k; xys.clear()) {
        for (uint32_t y = k + 1u; y <= (k << 1); ++y)
            if ((k * y) % (y - k) == 0)
                xys.push_back(pair<uint32_t, uint32_t>((y * k) / (y - k), y));

        cout << xys.size() << endl;
        for (auto &xy: xys)
            cout << "1/" << k << " = 1/" << xy.first << " + 1/" << xy.second << endl;
    }

    return 0;
}
