// #disjoint_set
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

struct edge
{
    uint16_t dsq;
    uint16_t m, n;

    edge()  {}

    edge(uint16_t dsq, uint16_t i, uint16_t j):
        dsq(dsq),
        m(min(i, j)),
        n(max(i, j))
    {}

    bool operator<(const edge &e) const
    {
        if (dsq != e.dsq)
            return dsq > e.dsq;
        else if (n != e.n)
            return n < e.n;
        else
            return m < e.m;
    }
};

uint16_t square(int16_t d) { return d * d; }

typedef pair<int16_t, int16_t> obstacle;

int main()
{
    vector<obstacle> obstacles(100);
    vector<uint16_t> set_ids(102);
    vector<edge> edges(101 * 100 + 200);

    auto get_set_id = [&set_ids](uint16_t i) {
        uint16_t s = i;
        while (set_ids[s] != s)
            s = set_ids[s];
        for (uint16_t j; (j = set_ids[i]) != s; i = j)
            set_ids[j] = s;
        return s;
    };

    cout.setf(ios::fixed);
    cout.precision(4);

    uint32_t case_count;
    cin >> case_count;
    for (uint32_t case_number = 1; case_number <= case_count; case_number++) {
        int16_t length, width;
        uint16_t n;
        cin >> length >> width >> n;

        obstacles.resize(n);
        for (auto &o: obstacles)
            cin >> o.first >> o.second;

        n = remove_if(obstacles.begin(), obstacles.begin() + n,
            [width](const obstacle &o) { return o.second == 0 || o.second == width; })
            - obstacles.begin();

        sort(obstacles.begin(), obstacles.begin() + n);
        n = unique(obstacles.begin(), obstacles.begin() + n) - obstacles.begin();

        obstacles.resize(n + 2);
        const uint16_t bottom = n;
        const uint16_t top = n + 1;

        const uint16_t max_dsq = square(width);

        edges.clear();
        for (uint16_t i = 0; i < n; i++) {
            auto &o = obstacles[i];
            for (uint16_t j = i + 1; j < n; j++) {
                auto &p = obstacles[j];
                const uint16_t dsq = square(o.first - p.first) + square(o.second - p.second);
                if (dsq <= max_dsq)
                    edges.emplace_back(edge{ dsq, i, j });
            }

            const struct {
                uint16_t dsq;
                uint16_t index;
            } ends[2] = {
                { square(o.second),  bottom },
                { square(width - o.second), top } };
            for (const auto &e: ends)
                if (e.dsq <= max_dsq)
                    edges.emplace_back(edge{ e.dsq, i, e.index });
        }

        set_ids.resize(n + 2);
        iota(set_ids.begin(), set_ids.end(), 0);

        make_heap(edges.begin(), edges.end());
        uint16_t dsq = max_dsq;
        while (edges.size() > 0 && get_set_id(top) != get_set_id(bottom)) {
            const auto e = edges.front();
            pop_heap(edges.begin(), edges.end());
            edges.pop_back();
            dsq = e.dsq;
            set_ids[get_set_id(e.n)] = get_set_id(e.m);
        }

        cout << "Maximum size in test case " << case_number << " is " << sqrt(dsq) << "." << endl;
    }

    return 0;
}
