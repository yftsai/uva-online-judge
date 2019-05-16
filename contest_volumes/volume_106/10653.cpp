// #breadth_first_search #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<bool>> is_visited;
    vector<pair<int16_t, int16_t>> q, qnext;
    for (int16_t r, c; cin >> r >> c && r > 0; ) {
        is_visited.resize(r);
        for (auto &row: is_visited)
            row.assign(c, false);

        uint16_t row_count;
        cin >> row_count;
        for (uint16_t i = 0, rn, nb; i < row_count && cin >> rn >> nb; ++i)
            for (uint16_t j = 0, c; j < nb && cin >> c; ++j)
                is_visited[rn][c] = true;

        pair<int16_t, int16_t> start, end;
        cin >> start.first >> start.second >> end.first >> end.second;
        is_visited[start.first][start.second] = true;
        q.assign(1, start);

        uint16_t time = 0;
        for (; !is_visited[end.first][end.second]; q.swap(qnext), ++time) {
            qnext.clear();
            for (const auto p: q) {
                for (int16_t i: { p.first - 1, p.first + 1})
                    if (0 <= i && i < r && !is_visited[i][p.second]) {
                        is_visited[i][p.second] = true;
                        qnext.emplace_back(i, p.second);
                    }
                for (int16_t j: { p.second - 1, p.second + 1})
                    if (0 <= j && j < c && !is_visited[p.first][j]) {
                        is_visited[p.first][j] = true;
                        qnext.emplace_back(p.first, j);
                    }
            }
        }
        cout << time << endl;
    }

    return 0;
}
