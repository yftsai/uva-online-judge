// #breadth_first_search #vague
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    array<bool, 26> is_awake;
    array<vector<uint8_t>, 26> connections;
    vector<uint16_t> waking_areas;

    for (uint16_t n, m; cin >> n >> m; ) {
        fill(is_awake.begin(), is_awake.end(), false);

        char a, b;
        waking_areas.clear();
        for (int i = 0; i < 3 && cin >> a; ++i)
            waking_areas.push_back(a - 'A');
        for (auto &cs: connections)
            cs.clear();
        for (uint16_t i = 0; i < m && cin >> a >> b; ++i) {
            connections[a - 'A'].push_back(b - 'A');
            connections[b - 'A'].push_back(a - 'A');
        }

        int16_t year_count = -1;
        uint16_t waked_count = 0;
        for (; waking_areas.size() > 0; ++year_count) {
            for (auto a: waking_areas)
                is_awake[a] = true, ++waked_count;
            waking_areas.clear();

            for (uint16_t i = 0; i < is_awake.size(); ++i)
                if (!is_awake[i]) {
                    uint16_t awake_count = 0;
                    for (auto j: connections[i])
                        if (is_awake[j])
                            ++awake_count;
                    if (awake_count >= 3)
                        waking_areas.push_back(i);
                }
        }

        if (waked_count >= n)
            cout << "WAKE UP IN, " << year_count << ", YEARS" << endl;
        else
            cout << "THIS BRAIN NEVER WAKES UP" << endl;
    }

    return 0;
}
