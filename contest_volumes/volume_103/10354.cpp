// #shortest_path
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <set>
#include <vector>
using namespace std;

constexpr uint16_t UNREACHABLE = 102 * 100;

void get_distances(const vector<set<pair<uint16_t, uint16_t>>> &roads,
                   uint16_t src, vector<uint16_t> &distances)
{
    set<pair<uint16_t, uint16_t>> pq;
    fill(distances.begin(), distances.end(), UNREACHABLE);
    distances[src] = 0;
    pq.emplace(distances[src], src);

    while (!pq.empty()) {
        uint16_t d = pq.begin()->first;
        uint16_t p = pq.begin()->second;
        pq.erase(pq.begin());
        for (auto &r: roads[p]) {
            if (d + r.second < distances[r.first]) {
                pq.erase(pair<uint16_t, uint16_t>(distances[r.first], r.first));
                distances[r.first] = d + r.second;
                pq.emplace(distances[r.first], r.first);
            }
        }
    }
}

int main()
{
    uint16_t p, r, bh, of, yh, m;
    vector<set<pair<uint16_t, uint16_t>>> roads;
    vector<uint16_t> distances;
    vector<uint16_t> places;

    while (cin >> p >> r >> bh >> of >> yh >> m) {
        roads.resize(p);
        for (auto &rs: roads)
            rs.clear();

        for (uint16_t i = 0, p1, p2, d; i < r && cin >> p1 >> p2 >> d; i++) {
            roads[p1 - 1].emplace(p2 - 1, d);
            roads[p2 - 1].emplace(p1 - 1, d);
        }

        distances.resize(p);
        if (bh == yh || bh == m || of == yh || of == m)
            distances[yh - 1] = UNREACHABLE;
        else {
            get_distances(roads, bh - 1, distances);

            places.push_back(of - 1);
            while (!places.empty() || places.back() == m - 1) {
                uint16_t p = places.back();
                if (p == yh - 1 || p == m - 1)
                    break;
                else
                    places.pop_back();

                for (auto &r: roads[p]) {
                    if (distances[r.first] + r.second == distances[p])
                        places.push_back(r.first);
                    roads[r.first].erase(pair<uint16_t, uint16_t>(p, r.second));
                }
                roads[p].clear();
            }

            if (places.size() == 0)
                get_distances(roads, m - 1, distances);
            else {
                distances[yh - 1] = UNREACHABLE;
                places.clear();
            }
        }


        if (distances[yh - 1] == UNREACHABLE)
            cout << "MISSION IMPOSSIBLE." << endl;
        else
            cout << distances[yh - 1] << endl;
    }

    return 0;
}
