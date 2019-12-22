// #shortest_path #travelling_salesman
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

struct road
{
    uint32_t end;
    uint32_t length;
};

void find_shortest_distances(
    const vector<vector<road>> &roads,
    const uint32_t start,
    set<uint32_t> &&ends,
    vector<uint32_t> *distances)
{
    set<pair<uint32_t, uint32_t>> pq;
    (*distances)[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty() && ends.size() > 0) {
        const uint32_t i = pq.begin()->second;
        pq.erase(pq.begin());
        ends.erase(i);

        for (const road &r: roads[i]) {
            uint32_t d = (*distances)[i] + r.length;
            if (d < (*distances)[r.end]) {
                pq.erase(pair<uint32_t, uint32_t>((*distances)[r.end], r.end));
                pq.emplace(d, r.end);
                (*distances)[r.end] = d;
            }
        }
    }
}

uint32_t optimize_route(
    const vector<vector<uint32_t>> &paths,
    const uint32_t route,
    const uint32_t end,
    vector<vector<uint32_t>> *routes)
{
    const uint32_t r = route & ~(1u << end);
    uint32_t &d = (*routes)[route][end];
    if (d == numeric_limits<uint32_t>::max())
        for (uint32_t i = 0, mask = 1; mask < route ; ++i, mask <<= 1)
            if (i != end && (route & mask) != 0)
                d = min(d, optimize_route(paths, r, i, routes) + paths[i][end]);
    return d;
}


int main()
{
    uint32_t test_count, n, m;
    vector<vector<road>> roads;
    vector<uint32_t> stores, distances;
    vector<vector<uint32_t>> paths, routes;

    for (cin >> test_count; test_count > 0 && cin >> n >> m; --test_count) {
        uint32_t x, y, d;
        roads.assign(n, vector<road>());
        for (uint32_t i = 0; i < m && cin >> x >> y >> d; ++i) {
            roads[x].push_back(road{y, d});
            roads[y].push_back(road{x, d});
        }

        uint32_t s;
        cin >> s;
        stores.resize(s + 1);
        stores[0] = 0;
        for_each(stores.begin() + 1, stores.end(), [](uint32_t &s) { cin >> s; });

        paths.resize(s + 1);
        for (uint32_t i = 0; i < s + 1; ++i) {
            paths[i].resize(s + 1);
            for (uint32_t j = 0; j < i; ++j)
                paths[i][j] = paths[j][i];

            distances.assign(n, numeric_limits<uint32_t>::max());
            find_shortest_distances(
                roads,
                stores[i],
                set<uint32_t>(stores.begin() + i + 1, stores.end()),
                &distances);

            for (uint32_t j = i + 1; j < s + 1; ++j)
                paths[i][j] = distances[ stores[j] ];
        }

        routes.resize(1 << (s + 1));
        for (auto &rs: routes)
            rs.assign(s + 1, numeric_limits<uint32_t>::max());
        for (uint32_t i = 1; i < s + 1; ++i)
            routes[1 << i][i] = paths[0][i];
        const uint32_t route = (1 << (s + 1)) - 1;
        cout << optimize_route(paths, route, 0, &routes) << endl;
    }

    return 0;
}
