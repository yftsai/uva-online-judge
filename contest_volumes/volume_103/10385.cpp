#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main()
{
    vector<pair<double, double>> speeds;
    vector<uint16_t> rlimits, climits;

    cout.setf(ios::fixed);
    for (uint16_t t, n; cin >> t >> n; ) {
        speeds.resize(n);
        for (auto &p: speeds)
            cin >> p.first >> p.second;

        const double rs = speeds.back().first, cs = speeds.back().second;
        speeds.pop_back();
        auto get_margin = [&](double r) {
            double m = numeric_limits<double>::max();
            for (const auto &s: speeds)
                m = min(r / s.first + (t - r) / s.second - r / rs - (t - r) / cs, m);
            return m;
        };

        rlimits.clear();
        climits.clear();
        for (uint16_t i = 0; i < speeds.size(); i++) {
            double slope = 1 / speeds[i].first - 1 / rs + 1 / cs - 1 / speeds[i].second;
            if (slope < 0)
                rlimits.push_back(i);
            else if (slope > 0)
                climits.push_back(i);
        }

        double r = 0;
        double margin = numeric_limits<double>::lowest();
        if (rlimits.size() == 0)
            margin = get_margin(r = t);
        else if (climits.size() == 0)
            margin = get_margin(r);
        else
            for (auto i: rlimits)
                for (auto j: climits) {
                    const auto &si = speeds[i], &sj = speeds[j];
                    double rm = (t / si.second - t / sj.second)
                        / (1 / sj.first - 1 / sj.second + 1 / si.second - 1 / si.first);
                    rm = max(min(rm, (double)t), 0.0);
                    double m = get_margin(rm);
                    if (m > margin) {
                        r = rm;
                        margin = m;
                    }
                }

        if (margin >= 0) {
            cout.precision(0);
            cout << "The cheater can win by " << (margin * 60 * 60) << " seconds";
            cout.precision(2);
            cout << " with r = " << r << "km and k = " << (t - r) << "km." << endl;
        }
        else
            cout << "The cheater cannot win." << endl;
    }
    return 0;
}
