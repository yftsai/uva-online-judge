// #shortest_path
#include <iostream>
#include <vector>
#include <set>
#include <limits>
using namespace std;

int main()
{
    uint32_t test_count;
    uint16_t n, m, s, t;
    vector<vector<pair<uint16_t, uint16_t>>> connections;
    vector<uint32_t> latencies;
    const uint32_t unreachable = numeric_limits<uint32_t>::max();

    cin >> test_count;
    for (uint32_t test_number = 1; test_number <= test_count && cin >> n >> m >> s >> t; ++test_number) {
        connections.assign(n, vector<pair<uint16_t, uint16_t>>());
        for (uint16_t i = 0, u, v, w; i < m && cin >> u >> v >> w; ++i) {
            connections[u].emplace_back(v, w);
            connections[v].emplace_back(u, w);
        }

        latencies.assign(n, unreachable);
        multiset<pair<uint32_t, uint16_t>> pq;
        latencies[s] = 0;
        pq.emplace(0u, s);
        while (!pq.empty() && pq.begin()->second != t) {
            uint32_t d = pq.begin()->first;
            uint16_t u = pq.begin()->second;
            pq.erase(pq.begin());
            for (const auto &c: connections[u])
                if (latencies[c.first] == unreachable)
                    pq.emplace(latencies[c.first] = d + c.second, c.first);
                else if (d + c.second < latencies[c.first]) {
                    pq.erase(pair<uint32_t, uint16_t>(latencies[c.first], c.first));
                    pq.emplace(latencies[c.first] = d + c.second, c.first);
                }
        }

        cout << "Case #" << test_number << ": ";
        if (latencies[t] == unreachable)
            cout << "unreachable" << endl;
        else
            cout << latencies[t] << endl;
    }
    return 0;
}
