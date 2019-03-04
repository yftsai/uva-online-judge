#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<uint32_t>> events;
    vector<uint32_t> counts;
    bool is_first_case = true;
    for (uint32_t n; cin >> n; is_first_case = false) {
        events.resize(n);
        for (uint32_t i = 0, m; i < n && cin >> m; ++i) {
            events[i].resize(m);
            for (auto &e: events[i])
                cin >> e;
        }
        counts.assign(n, 0);
        for (uint32_t i = n; i > 0; --i) {
            if (events[i - 1u].size() == 0)
                counts[i - 1u] = 1;
            else
                for (auto e: events[i - 1u])
                    counts[i - 1u] += counts[e];

        }
        if (!is_first_case)
            cout << endl;
        cout << counts.front() << endl;
    }

    return 0;
}
