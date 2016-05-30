// # trivial #graph
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i=1; i<=t; ++i) {
        int n, m;
        cin >> n >> m;
        vector<int> unit(n);
        for (auto &u: unit)
            cin >> u;
        vector<set<int>> edge(n);
        for (int j=0, u, v; j<m; ++j) {
            cin >> u >> v;
            edge[u].insert(v);
        }

        int node = 0, total = 0;
        while (edge[node].size() > 0) {
            int next = *edge[node].begin();
            for (auto v: edge[node])
                if (unit[v] > unit[next])
                    next = v;
            node = next, total += unit[next];
        }

        cout << "Case " << i << ": " << total << " " << node << endl;
    }

    return 0;
}
