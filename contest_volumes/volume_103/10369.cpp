// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

struct edge
{
    uint16_t ends[2];
    double distance;

    bool operator<(const edge &e) const
    {
        return distance < e.distance;
    }
};

int main()
{
    uint32_t n;
    uint16_t s, p;
    vector<pair<int16_t, int16_t>> outposts;
    vector<edge> edges;

    vector<uint16_t> set_ids;
    auto get_set_id = [&set_ids](uint16_t i) {
        uint16_t s = i;
        for (; s != set_ids[s]; s = set_ids[s])
            ;
        for (uint16_t j = i, k; j != s; j = k) {
            k = set_ids[j];
            set_ids[j] = s;
        }
        return s;
    };

    cout.precision(2);
    cout.setf(ios::fixed);
    for (cin >> n; n > 0 && cin >> s >> p; --n) {
        outposts.resize(p);
        edges.resize(uint32_t(p) * (p - 1u) / 2u);
        for (uint32_t i = 0, k = 0; i < p && cin >> outposts[i].first >> outposts[i].second; ++i)
            for (uint16_t j = 0; j < i; ++j, ++k) {
                edges[k].ends[0] = i;
                edges[k].ends[1] = j;
                edges[k].distance = sqrt(pow(outposts[i].first  - outposts[j].first,  2)
                                       + pow(outposts[i].second - outposts[j].second, 2));
            }
        sort(edges.begin(), edges.end());

        set_ids.resize(p);
        uint32_t set_count = p;
        iota(set_ids.begin(), set_ids.end(), 0);
        double d = 0;
        for (auto it = edges.begin(); it != edges.end() && set_count > s; ++it) {
            uint16_t f = get_set_id(it->ends[0]);
            uint16_t g = get_set_id(it->ends[1]);
            if (f != g) {
                set_ids[f] = g;
                --set_count;
                d = it->distance;
            }
        }
        cout << d << endl;
    }

    return 0;
}
