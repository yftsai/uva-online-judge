// #depth_first_search
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct station
{
    uint16_t number;
    int pigeon_value;
    vector<uint16_t> connected_stations;
    uint16_t index;
    uint16_t min_index;

    bool operator<(const station &s) const
    {
        if (pigeon_value != s.pigeon_value)
            return pigeon_value < s.pigeon_value;
        else
            return number > s.number;
    }
};

int main()
{
    vector<station> stations;
    vector<pair<uint16_t, vector<uint16_t>::iterator>> stack;

    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        stations.resize(n);
        for (uint16_t i = 0; i < n; ++i) {
            stations[i].number = i;
            stations[i].pigeon_value = 0;
            stations[i].connected_stations.clear();
            stations[i].index = n;
        }
        for (int x, y; cin >> x >> y && x >= 0; ) {
            stations[x].connected_stations.push_back(y);
            stations[y].connected_stations.push_back(x);
        }

        stack.assign(1, make_pair(0, stations[0].connected_stations.begin()));
        uint16_t indexed_count = 0;
        while (stack.size() > 0) {
            uint16_t s = stack.back().first;
            auto &it = stack.back().second;
            if (stations[s].index == n)
                stations[s].index = stations[s].min_index = (indexed_count++);
            else {
                stations[s].min_index = min(stations[s].min_index, stations[*it].min_index);
                if (stations[*it].min_index >= stations[s].index)
                    ++stations[s].pigeon_value;
            }

            for (; it != stations[s].connected_stations.end() && stations[*it].index != n; ++it)
                if (stack.size() >= 2u && stack[stack.size() - 2u].first != *it)
                    stations[s].min_index = min(stations[s].min_index, stations[*it].index);

            if (it == stations[s].connected_stations.end())
                stack.pop_back();
            else {
                ++stations[*it].pigeon_value;
                stack.emplace_back(*it, stations[*it].connected_stations.begin());
            }
        }

        make_heap(stations.begin(), stations.end());
        for (; m > 0; --m, stations.pop_back()) {
            cout << stations.front().number << " " << stations.front().pigeon_value << endl;
            pop_heap(stations.begin(), stations.end());
        }
        cout << endl;
    }

    return 0;
}
