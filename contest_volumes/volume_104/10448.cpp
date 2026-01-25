// #coin_change
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <vector>
using namespace std;

int main()
{
    uint16_t inputs, n, m;
    vector<map<uint16_t, int>> roads;

    vector<uint16_t> parents;   // form the path
    vector<uint16_t> stack;     // for DFS

    vector<int> rows[2];        // last two rows of the DP table
    constexpr int infinity = numeric_limits<int>::max();

    for (cin >> inputs; inputs > 0 && cin >> n >> m; inputs--) {
        roads.resize(n);
        for (auto &rs: roads)
            rs.clear();

        uint16_t id1, id2;
        int32_t c;
        for (uint16_t i = 0; i < m; i++) {
            cin >> id1 >> id2 >> c;
            roads[id1 - 1][id2 - 1] = c;
            roads[id2 - 1][id1 - 1] = c;
        }

        uint16_t k;
        cin >> k;
        for (uint16_t i = 0; i < k; i++) {
            cin >> id1 >> id2 >> c;
            id1--;
            id2--;

            // find the unique path
            parents.clear();
            parents.resize(n, n);
            parents[id1] = id1;
            stack.clear();
            stack.push_back(id1);
            do {
                uint16_t u = stack.back();
                stack.pop_back();
                for (auto &r: roads[u])
                    if (parents[r.first] == n) {
                        parents[r.first] = u;
                        stack.push_back(r.first);
                    }
            } while (!stack.empty() && parents[id2] == n);

            rows[1].resize(c + 1);
            fill(rows[1].begin(), rows[1].end(), infinity);
            if (parents[id2] != n) {
                uint16_t u = parents[id2];
                auto ce = roads[id2][u];
                if (ce <= c)
                    rows[1][ce] = 1;

                rows[0].resize(c + 1);
                for (; u != id1; u = parents[u]) {
                    rows[0].swap(rows[1]);
                    fill(rows[1].begin(), rows[1].end(), infinity);

                    auto cr = roads[u][ parents[u] ];
                    for (int cost = ce; cost <= c - cr; cost++) {
                        if (rows[0][cost] != infinity)
                            rows[1][cost + cr] = min(rows[0][cost] + 1, rows[1][cost + cr]);

                        if (rows[1][cost] != infinity && cost + 2 * cr <= c)
                            rows[1][cost + 2 * cr] = min(rows[1][cost] + 2, rows[1][cost + 2 * cr]);
                    }
                }
            }

            if (rows[1][c] != infinity)
                cout << "Yes " << rows[1][c] << endl;
            else
                cout << "No" << endl;
        }
        if (inputs > 1)
            cout << endl;
    }

    return 0;
}
