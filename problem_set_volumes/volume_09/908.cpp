// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct line_t
{
    uint32_t sites[2];
    uint32_t cost;
};

int main()
{
    vector<line_t> lines(1000 * 1000 + 11);
    vector<uint32_t> set_reps(lines.size());
    auto get_set_rep = [&set_reps](uint32_t i) {
        uint32_t s = i;
        while (set_reps[s] != s)
            s = set_reps[s];
        for (uint32_t j = i, k; (k = set_reps[j]) != s; j = k)
            set_reps[j] = s;
        return s;
    };

    bool is_first_case = true;
    for (uint32_t n; cin >> n; is_first_case = false) {
        lines.resize(n - 1);

        uint32_t original_cost = 0;
        for (auto &line: lines) {
            cin >> line.sites[0] >> line.sites[1] >> line.cost;
            original_cost += line.cost;
        }

        uint32_t k;
        cin >> k;
        lines.resize(n - 1 + k);
        for (uint32_t i = 0; i < k; ++i)
            cin >> lines[n - 1 + i].sites[0] >> lines[n - 1 + i].sites[1] >> lines[n - 1 + i].cost;

        lines.resize(n + k);
        uint32_t m;
        cin >> m;
        for (uint32_t i = 0; i < m; ++i)
            cin >> lines.back().sites[0] >> lines.back().sites[1] >> lines.back().cost;

        sort(lines.begin(), lines.end(),
            [](const line_t &c, const line_t &d) { return c.cost < d.cost; });

        set_reps.resize(n);
        iota(set_reps.begin(), set_reps.end(), 0);
        uint32_t new_cost = 0;
        for (const auto line: lines) {
            const uint32_t s = get_set_rep(line.sites[0] - 1);
            const uint32_t t = get_set_rep(line.sites[1] - 1);
            if (s != t) {
                set_reps[s] = t;
                new_cost += line.cost;
            }
        }

        if (!is_first_case)
            cout << endl;
        cout << original_cost << endl;
        cout << new_cost << endl; 
    }
    return 0;
}
