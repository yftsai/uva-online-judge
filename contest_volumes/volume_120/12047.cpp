// #shortest_path
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct road
{
    uint16_t u, v;  // from `u` to `v`
    int32_t c;

    bool operator<(const road &r) const { return c < r.c; }
};

void get_shortest_path(
    const vector<vector<pair<uint16_t, int32_t>>> &adjs,
    uint16_t s,
    vector<int32_t> &costs)
{
    costs.resize(adjs.size());
    fill(costs.begin(), costs.end(), -1);
    costs[s] = 0;

    set<pair<int32_t, uint16_t>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
        int32_t c = pq.begin()->first;
        uint16_t i = pq.begin()->second;
        pq.erase(pq.begin());
        for (auto &jc: adjs[i]) {
            if (costs[jc.first] < 0 || c + jc.second < costs[jc.first]) {
                if (costs[jc.first] >= 0)
                    pq.erase(pair<int32_t, uint16_t>(costs[jc.first], jc.first));
                costs[jc.first] = c + jc.second;
                pq.emplace(costs[jc.first], jc.first);
            }
        }
    }
}

int main()
{
    uint16_t ncases, n, s, t;
    int32_t m, p;
    vector<road> roads;
    vector<vector<pair<uint16_t, int32_t>>> adjs;
    vector<int32_t> from, to;

    for (cin >> ncases; ncases > 0 && cin >> n >> m >> s >> t >> p; ncases--) {
        adjs.resize(n + 1);
        for (auto &as: adjs)
            as.clear();

        roads.resize(m);
        for (auto &r: roads) {
            cin >> r.u >> r.v >> r.c;
            adjs[r.u].emplace_back(r.v, r.c);
        }

        get_shortest_path(adjs, s, from);

        if (0 > from[t] || from[t] > p)
            cout << -1 << endl;
        else {
            for (auto &as: adjs)
                as.clear();
            for (const auto &r: roads)
                adjs[r.v].emplace_back(r.u, r.c);
            get_shortest_path(adjs, t, to);

            make_heap(roads.begin(), roads.end());
            while (from[roads.front().u] < 0 || to[roads.front().v] < 0
                  || from[roads.front().u] + roads.front().c + to[roads.front().v] > p) {
                pop_heap(roads.begin(), roads.end());
                roads.pop_back();
            }
            cout << roads.front().c << endl;
        }
    }

    return 0;
}
