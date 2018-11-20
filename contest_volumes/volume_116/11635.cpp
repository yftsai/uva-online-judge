// #shortest_path
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    const int drive_time_limit = 600;
    vector<vector<pair<int, int>>> roads;
    vector<int> cs;
    vector<int> drive_times;

    for (int n, h; cin >> n >> h && n != 0; ) {
        cs.resize(h);
        for (auto &c: cs) {
            cin >> c;
            c--;
        }

        roads.assign(n, vector<pair<int, int>>());
        int m, a, b, t;
        for (cin >> m; m > 0 && cin >> a >> b >> t; m--) {
            roads[a - 1].emplace_back(b - 1, t);
            roads[b - 1].emplace_back(a - 1, t);
        }

        drive_times.assign(n, drive_time_limit + 1);
        set<pair<int, int>> updated_cities;
        updated_cities.emplace(drive_times[n - 1] = 0, n - 1);
        int night_count = -1;
        for (; updated_cities.size() > 0 && drive_times[0] > drive_time_limit; night_count++) {
            while (updated_cities.size() > 0) {
                int a = updated_cities.begin()->second;
                updated_cities.erase(updated_cities.begin());
                for (auto &bt: roads[a]) {
                    int t = drive_times[a] + bt.second;
                    if (t < drive_times[bt.first] && t <= drive_time_limit) {
                        updated_cities.erase(make_pair(drive_times[bt.first], bt.first));
                        updated_cities.emplace(drive_times[bt.first] = t, bt.first);
                    }
                }
            }
            for (auto c: cs)
                if (0 < drive_times[c] && drive_times[c] <= drive_time_limit)
                    updated_cities.emplace(drive_times[c] = 0, c);
        }

        cout << ((drive_times[0] <= drive_time_limit) ? night_count : -1) << endl;
    }

    return 0;
}
