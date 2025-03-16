// #set_union
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct province
{
    uint16_t parent;
    uint16_t size;
};

int main()
{
    vector<province> provinces(500);

    auto get_parent = [&provinces](uint16_t p) {
        uint16_t q = p;
        while (provinces[q].parent != q)
            q = provinces[q].parent;
        for (uint16_t t; (t = provinces[p].parent) != q; p = t)
            provinces[p].parent = q;
        return q;
    };

    vector<pair<uint16_t, uint16_t>> edges(500 * 500);
    for (uint32_t n, m; cin >> n >> m && n > 0; ) {
        int32_t p = numeric_limits<int32_t>::min(), q;
        uint16_t c, d;
        edges.clear();
        for (uint32_t i = 0; i < m && cin >> c >> d >> q; i++)
            if (q == p)
                edges.emplace_back(c, d);
            else if (q > p) {
                edges.clear();
                edges.emplace_back(c, d);
                p = q;
            }

        provinces.resize(n);
        for (uint16_t i = 0; i < n; i++) {
            provinces[i].parent = i;
            provinces[i].size = 1;
        }

        uint16_t max_size = 1;
        for (const auto &e: edges) {
            c = get_parent(e.first - 1);
            d = get_parent(e.second - 1);
            if (c != d) {
                provinces[d].parent = c;
                provinces[c].size += provinces[d].size;
                max_size = max(provinces[c].size, max_size);
            }
        }

        cout << max_size << endl;
    }

    return 0;
}
