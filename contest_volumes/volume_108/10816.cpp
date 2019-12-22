// #shortest_path
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct path
{
    uint16_t y, r, d;
};

struct oasis
{
    uint16_t parent, set;
    uint32_t distance;
    vector<path> paths;
};

int main()
{
    typedef pair<uint16_t, path> src_path;
    vector<src_path> paths;
    vector<oasis> oases;
    vector<uint16_t> shortest_path;

    const auto greater = [](const src_path &p, const src_path &q) {
        return p.second.r > q.second.r;
    };
    const auto get_set = [&oases](uint16_t s) {
        uint16_t t = s;
        while (oases[t].set != t)
            t = oases[t].set;
        for (uint16_t u; (u = oases[s].set) != t; s = u)
            oases[s].set = t;
        return t;
    };

    for (uint16_t n, e; cin >> n >> e; ) {
        uint16_t s, t;
        cin >> s >> t;

        paths.resize(e);
        for (auto &p: paths) {
            uint16_t x, y, ir, fr, id, fd;
            char dot;
            cin >> x >> y >> ir >> dot >> fr >> id >> dot >> fd;
            p.first = x - 1;
            p.second = path{uint16_t(y - 1), uint16_t(ir * 10 + fr), uint16_t(id * 10 + fd)};
        }

        oases.resize(n);
        for (uint16_t i = 0; i < n; ++i) {
            oases[i].parent = oases[i].set = i;
            oases[i].distance = numeric_limits<uint32_t>::max();
            oases[i].paths.clear();
        }

        uint16_t max_temp;
        make_heap(paths.begin(), paths.end(), greater);
        while (!paths.empty() && get_set(s - 1) != get_set(t - 1)) {
            max_temp = paths.front().second.r;
            while (!paths.empty() && paths.front().second.r == max_temp) {
                auto x = paths.front().first;
                auto &path = paths.front().second;
                auto y = path.y;

                oases[x].paths.push_back(path);
                oases[y].paths.push_back(path);
                oases[y].paths.back().y = x;

                oases[get_set(x)].set = get_set(y);

                pop_heap(paths.begin(), paths.end(), greater);
                paths.pop_back();
            }
        }

        oases[s - 1].distance = 0;
        set<pair<uint32_t, uint16_t>> pq;
        pq.emplace(0, s - 1);
        while (!pq.empty() && pq.begin()->first < oases[t - 1].distance) {
            uint32_t d = pq.begin()->first;
            uint16_t o = pq.begin()->second;
            pq.erase(pq.begin());
            for (const auto &p: oases[o].paths)
                if (d + p.d < oases[p.y].distance) {
                    pq.erase(pair<uint32_t, uint16_t>(oases[p.y].distance, p.y));
                    oases[p.y].distance = d + p.d;
                    oases[p.y].parent = o;
                    pq.emplace(d + p.d, p.y);
                }
        }

        shortest_path.clear();
        for (auto o = t - 1; o != s - 1; o = oases[o].parent)
            shortest_path.push_back(o);

        cout << s;
        for (auto it = shortest_path.rbegin(); it != shortest_path.rend(); ++it)
            cout << " " << (*it + 1);
        cout << endl;

        cout << (oases[t - 1].distance / 10) << "." << (oases[t - 1].distance % 10);
        cout << " " << (max_temp / 10) << "." << (max_temp % 10) << endl;
    }

    return 0;
}
