// #spanning_tree
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

struct island
{
    int32_t x, y;
    int32_t m;
    double t;
};

int main()
{
    vector<island> islands;
    vector<vector<double>> dists;

    cout.setf(ios::fixed);
    cout.precision(2);
    for (uint32_t gnum = 1, n; cin >> n && n > 0; gnum++) {
        islands.resize(n);
        for (auto &i: islands) {
            cin >> i.x >> i.y >> i.m;
            i.t = numeric_limits<double>::max();
        }

        dists.resize(n);
        for (uint16_t i = 0; i < n; i++) {
            dists[i].resize(n - 1 - i);
            for (uint16_t j = 0; i + 1u + j < n; j++) {
                auto dx = islands[i].x - islands[i + 1 + j].x;
                auto dy = islands[i].y - islands[i + 1 + j].y;
                dists[i][j] = sqrt(dx * dx + dy * dy);
            }
        }

        priority_queue<pair<double, uint16_t>> pq;
        islands[0].t = 0;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();
            if (islands[p.second].t == -p.first)
                for (uint16_t i = 0; i < n; i++) {
                    if (i != p.second) {
                        auto d = (i < p.second) ? dists[i][p.second - 1 - i] : dists[p.second][i - 1 - p.second];
                        auto t = max(islands[p.second].t, d);
                        if (t < islands[i].t) {
                            islands[i].t = t;
                            pq.emplace(-islands[i].t, i);
                        }
                    }
                }
        }

        double sum_tm = 0;
        double sum_m  = 0;
        for (auto &i: islands) {
            sum_tm += i.t * i.m;
            sum_m  += i.m;
        }
        cout << "Island Group: " << gnum
             << " Average " << sum_tm / sum_m << endl;
        cout << endl;
    }

    return 0;
}
