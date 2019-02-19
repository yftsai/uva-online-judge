// #breadth_first_search
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

bool is_valid(const vector<vector<char>> &squares, const pair<int16_t, int16_t> &p)
{
    return 0 < p.first && p.first < int(squares.size())
        && 0 < p.second && p.second < int(squares[p.first].size())
        && squares[p.first - 1][p.second - 1] == '0'
        && squares[p.first - 1][p.second] == '0'
        && squares[p.first][p.second - 1] == '0'
        && squares[p.first][p.second] == '0';
}

int main()
{
    const map<char, uint16_t> dir_indexes = { {'n', 0}, {'e', 1}, {'w', 2}, {'s', 3} };
    const pair<int16_t, int16_t> steps[] = {
        {-1,  0},
        { 0,  1},
        { 0, -1},
        { 1,  0}
    };
    const array<uint16_t, 2> turns[] = {
        { dir_indexes.at('e'),  dir_indexes.at('w') },
        { dir_indexes.at('n'),  dir_indexes.at('s') },
        { dir_indexes.at('n'),  dir_indexes.at('s') },
        { dir_indexes.at('e'),  dir_indexes.at('w') }
    };
    const int unreachable = 50 * 50 * 4 + 1;

    vector<vector<char>> squares;
    vector<vector<array<int, 4>>> distances;
    string orientation;
    for (uint16_t m, n; cin >> m >> n && m != 0; ) {
        squares.resize(m);
        for (uint16_t i = 0; i < m; ++i) {
            squares[i].resize(n);
            for (char &s: squares[i])
                cin >> s;
        }

        distances.resize(m);
        for (auto &rows: distances) {
            rows.resize(n);
            for (auto &square: rows)
                fill(square.begin(), square.end(), unreachable);
        }

        pair<int16_t, int16_t> b, e;
        queue<pair<int16_t, int16_t>> ps;
        queue<uint16_t> dirs;
        cin >> b.first >> b.second >> e.first >> e.second >> orientation;
        if (is_valid(squares, b)) {
            uint16_t dir = dir_indexes.at(orientation[0]);
            distances[b.first][b.second][dir] = 0;
            ps.push(b);
            dirs.push(dir);
        }

        while (!ps.empty()) {
            const pair<int16_t, int16_t> p = ps.front();
            ps.pop();
            const uint16_t dir = dirs.front();
            dirs.pop();
            auto &dists = distances[p.first][p.second];

            pair<int16_t, int16_t> q = p;
            const auto step = steps[dir];
            for (uint16_t i = 0; i < 3; ++i) {
                q.first += step.first;
                q.second += step.second;

                if (!is_valid(squares, q))
                    break;
                else if (dists[dir] + 1 < distances[q.first][q.second][dir]) {
                    distances[q.first][q.second][dir] = dists[dir] + 1;
                    ps.push(q);
                    dirs.push(dir);
                }
            }

            for (const uint16_t &next_dir: turns[dir])
                if (dists[dir] + 1 < dists[next_dir]) {
                    dists[next_dir] = dists[dir] + 1;
                    ps.push(p);
                    dirs.push(next_dir);
                }
        }

        int end_distance = is_valid(squares, e)
            ? *min_element(distances[e.first][e.second].begin(), distances[e.first][e.second].end())
            : -1;
        cout << ((end_distance == unreachable) ? -1 : end_distance) << endl;
    }

    return 0;
}
