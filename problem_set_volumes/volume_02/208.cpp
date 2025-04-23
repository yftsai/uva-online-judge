// #depth_first_search
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

void reach(const vector<vector<uint16_t>> &graph,
           uint16_t dst, uint16_t i,
           bitset<22> &reachable)
{
    for (auto j: graph[i])
        if (!reachable[j]) {
            reachable.set(j);
            reach(graph, dst, j, reachable);
            if (reachable[dst])
                return;
        }
}

void enumerate(const vector<vector<uint16_t>> &graph,
               bitset<22> &visited, vector<uint16_t> &path,
               uint16_t dst, uint16_t i,
               uint64_t &count)
{
    if (i == dst) {
        count++;
        for (auto c: path)
            cout << c << " ";
        cout << dst << endl;
    }
    else {
        auto reachable = visited;
        reach(graph, dst, i, reachable);

        if (reachable[dst]) {
            visited.set(i);
            path.push_back(i);

            for (auto j: graph[i])
                if (!visited[j]) {
                    enumerate(graph,
                              visited, path,
                              dst, j,
                              count);
                }

            visited.reset(i);
            path.pop_back();
        }
    }
}

int main()
{
    vector<vector<uint16_t>> graph(22);
    vector<uint16_t> path;

    for (uint32_t cn = 1, dst; cin >> dst; cn++) {
        for (auto &cs: graph)
            cs.clear();
        bitset<22> visited;

        for (uint16_t i, j; cin >> i >> j && i != 0; ) {
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
        for (auto &js: graph) {
            sort(js.begin(), js.end());
            js.resize(unique(js.begin(), js.end()) - js.begin());
        }

        cout << "CASE " << cn << ":" << endl;
        uint64_t count = 0;
        enumerate(graph,
                  visited, path,
                  dst, 1,
                  count);
        cout << "There are " << count
             << " routes from the firestation to streetcorner " << dst << "." << endl;
    }

    return 0;
}
