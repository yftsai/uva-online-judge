// #shortest_path
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <vector>
using namespace std;

enum class station_t: uint8_t { unknown, secondary, important };

int main()
{
    uint32_t tests;
    uint16_t n, s;
    vector<station_t> station_types;
    vector<vector<uint16_t>> lines;

    map<uint16_t, uint16_t> indexes;
    vector<vector<uint16_t>> distances;

    for (cin >> tests; tests > 0 && cin >> n >> s; tests--) {
        station_types.clear();
        station_types.resize(n, station_t::unknown);

        lines.resize(s);
        for (auto &l: lines) {
            uint16_t station;
            l.clear();
            while (cin >> station && station != 0) {
                station--;
                l.push_back(station);
                auto &type = station_types[station];
                if (type == station_t::unknown)
                    type = station_t::secondary;
                else if (type == station_t::secondary)
                    type = station_t::important;
            }
        }

        indexes.clear();
        for (uint16_t i = 0; i < n; i++)
            if (station_types[i] == station_t::important)
                indexes.emplace_hint(indexes.end(), i, indexes.size());

        distances.resize(indexes.size());
        for (auto &ds: distances) {
            ds.clear();
            ds.resize(indexes.size(), numeric_limits<uint16_t>::max() / 2);
        }

        for (auto &line: lines) {
            uint16_t li = 0;
            while (station_types[ line[li] ] != station_t::important)
                li++;
            for (uint16_t lj; li < line.size(); li = lj) {
                lj = li + 1;
                while (lj < line.size() && station_types[ line[lj] ] == station_t::secondary)
                    lj++;

                if (station_types[ line[li] ] != station_t::important)
                    li--;
                uint16_t i = indexes[ line[li] ];

                if (lj < line.size()) {
                    uint16_t j = indexes[ line[lj] ];
                    distances[i][j] = min<uint16_t>(lj - li, distances[i][j]);
                    distances[j][i] = min<uint16_t>(lj - li, distances[i][j]);
                }
            }
        }

        for (uint16_t k = 0; k < distances.size(); k++)
            for (uint16_t i = 0; i < distances.size(); i++)
                if (k != i)
                    for (uint16_t j = 0; j < distances.size(); j++)
                        if (k != j && i != j)
                            distances[i][j] = min<uint16_t>(distances[i][k] + distances[k][j], distances[i][j]);

        uint16_t ks = 0;
        uint16_t dist = numeric_limits<uint16_t>::max();
        for (auto &m: indexes) {
            uint16_t i = m.second;
            uint16_t d = 0;
            for (uint16_t j = 0; j < distances[i].size(); j++) {
                if (i != j)
                    d += distances[i][j];
            }
            if (d < dist) {
                dist = d;
                ks = m.first;
            }
        }
        cout << "Krochanska is in: " << ks + 1 << endl;
    }

    return 0;
}
