// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
using namespace std;

struct edge
{
    uint16_t n, m;
    uint32_t dsq;

    bool operator<(const edge &e) const
    {
        return dsq < e.dsq;
    }
};

typedef pair<int16_t, int16_t> location;

uint32_t get_distance_square(const location &c, const location &d)
{
    int32_t x = c.first - d.first;
    int32_t y = c.second - d.second;
    return x * x + y * y;
}

uint16_t get_state(vector<uint16_t> &states, uint16_t n)
{
    uint16_t s = n;
    for (; states[s] != s; s = states[s])
        ;
    for (uint16_t i = n, j; i != s; i = j) {
        j = states[i];
        states[i] = s;
    }
    return s;
}

int main()
{
    vector<location> cities;
    vector<edge> edges;
    vector<uint16_t> states;

    uint16_t t, n, r;
    cin >> t;
    for (uint16_t test_number = 1; test_number <= t && cin >> n >> r; ++test_number) {
        cities.resize(n);
        edges.resize(uint32_t(n - 1u) * n / 2u);
        for (uint32_t i = 0, e = 0; i < n && cin >> cities[i].first >> cities[i].second; ++i)
            for (uint16_t j = 0; j < i; ++j, ++e) {
                edges[e].n = i;
                edges[e].m = j;
                edges[e].dsq = get_distance_square(cities[i], cities[j]);
            }

        states.resize(n);
        iota(states.begin(), states.end(), 0);
        const uint32_t rsq = uint32_t(r) * r;
        double road_length = 0, rail_length = 0;
        uint16_t state_count = n;
        sort(edges.begin(), edges.end());
        for (const edge &e: edges) {
            uint16_t n = get_state(states, e.n);
            uint16_t m = get_state(states, e.m);
            if (n != m) {
                states[n] = m;
                if (e.dsq <= rsq) {
                    road_length += sqrt(e.dsq);
                    --state_count;
                }
                else
                    rail_length += sqrt(e.dsq);
            }
        }

        cout << "Case #" << test_number << ": "
             << state_count << " "
             << round(road_length) << " "
             << round(rail_length) << endl;
    }

    return 0;
}
