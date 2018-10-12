#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    const int unvisited_mask = 1 << 28, distance_mask = 0xFFFFFF0, cost_mask = 0xF;
    auto get_distance = [](int m) { return (m & distance_mask) >> 4; };
    auto get_cost = [](int m) { return m & cost_mask; };

    int case_count, m, n, maze[999][999];
    vector<tuple<int, int16_t, int16_t>> q;
    for (cin >> case_count; case_count > 0 && cin >> m >> n; case_count--, q.clear()) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n && cin >> maze[i][j]; j++)
                maze[i][j] |= unvisited_mask | distance_mask;

        q.emplace_back(-get_cost(maze[0][0]), 0, 0);
        while ((maze[m - 1][n - 1] & unvisited_mask) != 0) {
            pop_heap(q.begin(), q.end());
            int16_t r = get<1>(q.back()), c = get<2>(q.back());
            maze[r][c] = -get<0>(q.back());
            q.pop_back();

            for (int16_t i: { max(0, r - 1), min(m - 1, r + 1) }) {
                int &m = maze[i][c], cost = get_cost(maze[i][c]);
                if ((m & unvisited_mask) != 0 && maze[r][c] + cost < get_distance(m)) {
                    int d = maze[r][c] + cost;
                    q.emplace_back(-d, i, c);
                    push_heap(q.begin(), q.end());
                    m = unvisited_mask | (d << 4) | cost;
                }
            }
            for (int16_t i: { max(0, c - 1), min(n - 1, c + 1)}) {
                int &m = maze[r][i], cost = get_cost(maze[r][i]);
                if ((m & unvisited_mask) != 0 && maze[r][c] + cost < get_distance(m)) {
                    int d = maze[r][c] + get_cost(m);
                    q.emplace_back(-d, r, i);
                    push_heap(q.begin(), q.end());
                    m = unvisited_mask | (d << 4) | cost;
                }
            }
        }
        cout << maze[m - 1][n - 1] << endl;
    }

    return 0;
}
