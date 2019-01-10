// #depth_first_search #strongly_connected_component
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<vector<int>> ins, outs;
    vector<bool> is_visited;
    vector<int> stack;
    for (int n, m; cin >> n >> m && n > 0; ) {
        ins.assign(n, vector<int>());
        outs.assign(n, vector<int>());
        for (int i = 0, v, w, p; i < m && cin >> v >> w >> p; ++i) {
            outs[v - 1].push_back(w - 1);
            ins[w - 1].push_back(v - 1);
            if (p == 2) {
                outs[w - 1].push_back(v - 1);
                ins[v - 1].push_back(w - 1);
            }
        }

        auto visit_all = [&stack, &is_visited](const vector<vector<int>> &edges) {
            is_visited.assign(edges.size(), false);
            is_visited[0] = true;
            stack.push_back(0);
            do {
                int n = stack.back();
                stack.pop_back();
                for (int m: edges[n])
                    if (!is_visited[m]) {
                        is_visited[m] = true;
                        stack.push_back(m);
                    }
            } while (!stack.empty());
            return all_of(is_visited.begin(), is_visited.end(), [](bool b) { return b; });
        };

        cout << ((visit_all(ins) && visit_all(outs)) ? 1 : 0) << endl;
    }

    return 0;
}
