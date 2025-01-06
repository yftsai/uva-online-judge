// #dynamic_programming
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct gangster
{
    uint16_t t;
    uint16_t p;
    int16_t s;

    bool operator<(const struct gangster &) const;
};

bool gangster::operator<(const struct gangster &g) const
{
    return t < g.t;
}

struct door
{
    int16_t lo, hi;
    uint16_t p;

    door():
        lo(0), hi(0), p(0) {}
    door(uint16_t l, uint16_t h, uint16_t p):
        lo(l), hi(h), p(p) {}
};

void update(vector<door> &ds, vector<door> &temp, door d)
{
    if (ds.empty())
        temp.push_back(d);
    else if (ds.back().hi < d.hi)
        temp.emplace_back(max(ds.back().hi, d.lo), d.hi, d.p);

    for (; !ds.empty() && d.hi < ds.back().lo; ds.pop_back())
        temp.push_back(ds.back());

    while (!ds.empty() && d.lo <= ds.back().hi) {
        // ds.back().lo <= d.hi
        if (d.hi < ds.back().hi) {
            temp.emplace_back(d.hi + 1, ds.back().hi, ds.back().p);
            ds.back().hi = d.hi;
        }
        else if (ds.back().lo < d.lo) {
            temp.emplace_back(d.lo, ds.back().hi, max(ds.back().p, d.p));
            ds.back().hi = d.lo - 1;
        }
        else {
            temp.emplace_back(ds.back().lo, ds.back().hi, max(ds.back().p, d.p));
            ds.pop_back();
        }
    }

    for (; !temp.empty(); temp.pop_back())
        if (!ds.empty() && ds.back().p == temp.back().p)
            ds.back().hi = temp.back().hi;
        else
            ds.push_back(temp.back());
}

int main()
{
    uint16_t m, n, k, t;
    vector<gangster> gs;
    vector<door> doors, ds, temp;
    for (cin >> m; m > 0 && cin >> n >> k >> t; m--) {
        gs.resize(n);
        for (auto &g: gs)
            cin >> g.t;
        for (auto &g: gs)
            cin >> g.p;
        for (auto &g: gs)
            cin >> g.s;

        sort(gs.begin(), gs.end());

        uint16_t current = 0;
        doors.clear();
        doors.resize(1);
        for (auto &g: gs) {
            ds.clear();
            for (const auto &d: doors) {
                auto lo = max<int16_t>(d.lo - int16_t(g.t - current), 0);
                auto hi = min<int16_t>(d.hi + (g.t - current), k);
                if (lo <= g.s && g.s <= hi) {
                    if (lo < g.s)
                        update(ds, temp, door(lo, g.s - 1, d.p));
                    update(ds, temp, door(g.s, g.s, d.p + g.p));
                    if (g.s < hi)
                        update(ds, temp, door(g.s + 1, hi, d.p));
                }
                else
                    update(ds, temp, door(lo, hi, d.p));
            }

            doors.swap(ds);
            current = g.t;
        }

        uint16_t max_p = 0;
        for (auto &d: doors)
            max_p = max(d.p, max_p);
        cout << max_p << endl;
        if (m > 1)
            cout << endl;
    }
    return 0;
}
