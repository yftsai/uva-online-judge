#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

typedef pair<double, double> point;

int main()
{
    const double max_distance = 10000;
    vector<point> points;
    for (int n; cin >> n && n != 0; ) {
        points.resize(n);
        for (point &p: points)
           cin >> p.first >> p.second;

        double d = max_distance;
        set<point> yxs;
        sort(points.begin(), points.end());
        for (auto b = points.begin(), e = points.begin(); e != points.end(); ++e) {
            for (; b != e && b->first < e->first - d; ++b)
                yxs.erase(point(b->second, b->first));

            point lbp(e->second - d, e->first);
            for (auto it = yxs.lower_bound(lbp); it != yxs.end() && it->first < e->second + d; ++it)
                d = min(d, sqrt(pow(it->first - e->second, 2) + pow(it->second - e->first, 2)));
            yxs.emplace(e->second, e->first);
        }

        if (d >= max_distance)
            cout << "INFINITY" << endl;
        else
            cout << fixed << setprecision(4) << d << endl;
    }
    return 0;
}
