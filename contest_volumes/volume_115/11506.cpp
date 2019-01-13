// #maximum_flow
#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <limits>
using namespace std;

int main()
{
    vector<map<int, int>> edges;
    auto add_edge = [&edges](int src, int dst, int cap) {
        auto it = edges[src].lower_bound(dst);
        if (it == edges[src].end() || it->first != dst)
            edges[src].emplace_hint(it, dst, cap);
        else
            it->second += cap;
    };
    vector<int> sources;
    vector<int> stack;

    for (int m, w; cin >> m >> w && m > 0; edges.clear()) {
        edges.resize(2 * m - 2);
        for (int j = 0, i, c; j < m - 2 && cin >> i >> c; ++j)
            edges[2 * i - 3][2 * i - 2] = c;
        for (int i = 0, j, k, d; i < w && cin >> j >> k >> d; ++i) {
            if (j != m && k != 1)
                add_edge(2 * j - 2, 2 * k - 3, d);
            if (k != m && j != 1)
                add_edge(2 * k - 2, 2 * j - 3, d);
        }


        sources.resize(edges.size());
        do {
            iota(sources.begin(), sources.end(), 0);
            for (stack.assign(1, 0); !stack.empty() && sources.back() == (2 * m - 3); ) {
                int s = stack.back();
                stack.pop_back();
                for (auto &e: edges[s])
                    if (e.second > 0 && sources[e.first] == e.first) {
                        sources[e.first] = s;
                        stack.push_back(e.first);
                    }
            }
            if (sources.back() != int(edges.size() - 1)) {
                int minc = numeric_limits<int>::max();
                for (int s = edges.size() - 1; s != 0; s = sources[s])
                    minc = min(minc, edges[ sources[s] ][s]);
                for (int s = edges.size() - 1; s != 0; s = sources[s]) {
                    add_edge(sources[s], s, -minc);
                    add_edge(s, sources[s], minc);
                }
            }
        } while (sources.back() != int(edges.size() - 1));


        auto add = [](int a, const pair<int, int> &p) { return a + p.second; };
        cout << accumulate(edges.back().begin(), edges.back().end(), 0, add) << endl;
    }

    return 0;
}
