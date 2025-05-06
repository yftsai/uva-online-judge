// #bipartite_matching
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

bool flow(int16_t n, int16_t dst,
          vector<vector<uint16_t>> &nodes,
          vector<bool> &visited)
{
    visited[n] = true;

    if (n == dst)
        return true;
    else {
        for (uint16_t i = 0; i < nodes[n].size(); i++) {
            uint16_t m = nodes[n][i];
            if (!visited[m] && flow(m, dst, nodes, visited)) {
                nodes[m].push_back(n);
                nodes[n][i] = nodes[n].back();
                nodes[n].pop_back();
                return true;
            }
        }
        return false;
    }
}

int main()
{
    vector<vector<int16_t>> board;
    vector<vector<uint16_t>> nodes;
    vector<bool> visited;

    string row;
    for (uint16_t n; cin >> n; ) {
        board.resize(n);
        nodes.clear();

        for (uint16_t i = 0; i < n && cin >> row; i++) {
            board[i].resize(n);
            for (uint16_t j = 0; j < n; j++)
                if (row[j] == 'X')
                    board[i][j] = -1;
                else {
                    if (j == 0 || row[j - 1] == 'X')
                        nodes.emplace_back();
                    board[i][j] = nodes.size() - 1;
                }
        }

        const uint16_t src = nodes.size();
        nodes.emplace_back();
        nodes.back().reserve(src);
        for (uint16_t i = 0; i < src; i++)
            nodes.back().push_back(i);

        const uint16_t dst = nodes.size();
        nodes.emplace_back();

        for (uint16_t j = 0; j < n; j++)
            for (uint16_t i = 0; i < n; i++)
                if (board[i][j] >= 0) {
                    if (i == 0 || board[i - 1][j] < 0)
                        nodes.emplace_back(1, dst);
                    nodes[ board[i][j] ].push_back(nodes.size() - 1);
                }

        uint16_t n_rooks = 0;
        visited.resize(nodes.size());
        auto try_flow = [&] {
            fill(visited.begin(), visited.end(), false);
            return flow(src, dst, nodes, visited);
        };
        while (try_flow())
            n_rooks++;
        cout << n_rooks << endl;
    }

    return 0;
}
