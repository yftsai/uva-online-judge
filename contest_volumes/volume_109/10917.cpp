// #shortest_path
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    const uint16_t office = 0, home = 1;
    const uint32_t unreachable = 1000 * 1000 * 1000 + 1;
    vector<vector<pair<uint16_t, uint32_t>>> edges;
    vector<uint32_t> distances;
    vector<uint32_t> route_counts;

    for (uint32_t n, m; cin >> n && n != 0 && cin >> m; ) {
        edges.clear();
        edges.resize(n);

        uint16_t a, b;
        for (uint32_t i = 0, d; i < m && cin >> a >> b >> d; i++) {
            edges[a - 1].emplace_back(b - 1, d);
            edges[b - 1].emplace_back(a - 1, d);
        }

        route_counts.resize(n);
        route_counts[office] = 0;
        distances.assign(n, unreachable);
        distances[home] = 0;

        set<pair<uint32_t, uint16_t>> pq;
        pq.emplace(distances[home], home);

        do {
            a = pq.begin()->second;
            pq.erase(pq.begin());

            route_counts[a] = (a == home) ? 1 : 0;
            for (const auto bd: edges[a])
                if (distances[bd.first] < distances[a])
                    route_counts[a] += route_counts[bd.first];
                else if (distances[a] + bd.second < distances[bd.first]) {
                    distances[bd.first] = distances[a] + bd.second;
                    pq.erase(pair<uint32_t, uint16_t>(distances[bd.first], bd.first));
                    pq.emplace(distances[bd.first], bd.first);
                }
        } while (a != office && !pq.empty());

        cout << route_counts[office] << endl;
    }
    return 0;
}
