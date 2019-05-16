// #shortest_path
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    vector<vector<pair<uint16_t, uint32_t>>> edges;
    vector<uint32_t> time;

    uint32_t case_count, t, m;
    uint16_t n, e;
    for (cin >> case_count; case_count > 0 && cin >> n >> e >> t >> m; --case_count) {
        edges.assign(n, vector<pair<uint16_t, uint32_t>>());
        for (uint32_t a, b, s; m > 0 && cin >> a >> b >> s; --m)
            edges[b - 1u].emplace_back(a - 1u, s);

        uint16_t escape_count = 1;
        time.assign(n, t + 1u);
        time[e - 1u] = 0;
        set<pair<uint32_t, uint16_t>> q = { pair<uint32_t, uint16_t>(0, e - 1u) };
        while (!q.empty()) {
            pair<uint32_t, uint16_t> state = *q.begin();
            q.erase(q.begin());
            for (auto at: edges[state.second]) {
                uint32_t s = state.first + at.second;
                if (s < time[at.first] && s <= t) {
                    if (time[at.first] <= t) {
                        q.erase(pair<uint32_t, uint16_t>(time[at.first], at.first));
                        q.emplace(s, at.first);
                    }
                    else {
                        q.emplace(s, at.first);
                        ++escape_count;
                    }
                    time[at.first] = s;
                }
            }
        }

        cout << escape_count << endl;
        if (case_count > 1)
            cout << endl;
    }
    return 0;
}
