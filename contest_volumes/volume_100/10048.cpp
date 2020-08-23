// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
    uint16_t crossings[2];
    int32_t level;
};

struct crossing
{
    uint16_t set_rep;
    vector<uint16_t> crossings;
    vector<int32_t> max_levels;
};

int main()
{
    vector<edge> edges;
    vector<crossing> crossings;

    auto get_set_rep = [&crossings](uint16_t i) {
        uint16_t s = i;
        while (crossings[s].set_rep != s)
            s = crossings[s].set_rep;
        for (uint16_t j = i, k; (k = crossings[j].set_rep) != s; j = k)
            crossings[j].set_rep = s;
        return s;
    };

    uint16_t c, s, q;
    bool is_first_case = true;
    for (uint16_t case_number = 1; cin >> c >> s >> q && c != 0; ++case_number, is_first_case = false) {
        if (!is_first_case)
            cout << endl;
        cout << "Case #" << case_number << endl;

        edges.resize(s);
        for (auto &e: edges) {
            cin >> e.crossings[0] >> e.crossings[1] >> e.level;
            --e.crossings[0];
            --e.crossings[1];
        }
        sort(edges.begin(), edges.end(),
            [](const edge &e, const edge &f) { return e.level < f.level; });

        const int32_t NO_PATH = -1;
        crossings.resize(c);
        for (uint16_t i = 0; i < c; ++i) {
            crossings[i].set_rep = i;
            crossings[i].crossings.assign(1, i);
            crossings[i].max_levels.assign(c, NO_PATH);
        }

        for (const auto &e: edges) {
            const uint16_t s1 = get_set_rep(e.crossings[0]);
            const uint16_t s2 = get_set_rep(e.crossings[1]);
            if (s1 != s2) {
                for (const uint16_t c1: crossings[s1].crossings)
                    for (const uint16_t c2: crossings[s2].crossings)
                        crossings[c1].max_levels[c2] = crossings[c2].max_levels[c1] = e.level;
                crossings[s1].set_rep = s2;
                crossings[s2].crossings.insert(crossings[s2].crossings.end(),
                    crossings[s1].crossings.begin(), crossings[s1].crossings.end());
            }
        }

        for (uint16_t i = 0, c1, c2; i < q && cin >> c1 >> c2; ++i) {
            if (crossings[c1 - 1].max_levels[c2 - 1] == NO_PATH)
                cout << "no path" << endl;
            else
                cout << crossings[c1 - 1].max_levels[c2 - 1] << endl;
        }
    }

    return 0;
}
