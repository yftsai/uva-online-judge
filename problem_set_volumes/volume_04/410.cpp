// #easy
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
using namespace std;

int main()
{
    vector<int16_t> masses;
    cout.setf(ios::fixed);
    cout.precision(5);
    for (uint16_t set_number = 1, c, s; cin >> c >> s; ++set_number) {
        masses.resize(s);
        for (auto &m: masses)
            cin >> m;
        sort(masses.begin(), masses.end(), std::greater<int16_t>());

        const double am = accumulate(masses.begin(), masses.end(), 0.0) / c;
        double imbalance = 0;
        cout << "Set #" << set_number << endl;
        uint16_t p = min(c, s), q = min(c, s);
        for (uint16_t i = 0; i < c; ++i) {
            cout << " " << i << ":";
            int16_t cm = 0;
            if (p > 0) {
                cout << " " << masses[p - 1];
                cm += masses[--p];
            }
            if (q < s) {
                cout << " " << masses[q];
                cm += masses[q++];
            }
            imbalance += abs(cm - am);
            cout << endl;
        }
        cout << "IMBALANCE = " << imbalance << endl;
        cout << endl;
    }

    return 0;
}
