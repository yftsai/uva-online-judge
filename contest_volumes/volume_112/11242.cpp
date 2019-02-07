// #trivial
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<uint16_t> front_sprockets;
    vector<double> ratios;
    cout.setf(ios::fixed);
    cout.precision(2);
    for (uint16_t f, r; cin >> f >> r && f != 0; ratios.clear()) {
        front_sprockets.resize(f);
        for (auto &f: front_sprockets)
            cin >> f;
        for (uint16_t i = 0, s; i < r && cin >> s; ++i)
            for (auto &f: front_sprockets)
                ratios.push_back(s / double(f));

        sort(ratios.begin(), ratios.end());
        double max_spread = 0;
        for (vector<double>::iterator it1 = ratios.begin(), it2; ++(it2 = it1) != ratios.end(); ++it1)
            max_spread = max(max_spread, *it2 / *it1);
        cout << max_spread << endl;
    }
    return 0;
}
