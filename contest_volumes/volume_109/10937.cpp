// #traveling_salesman_problem
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

void traverse(const vector<vector<char>> &island,
              pair<int16_t, int16_t> start,
              vector<vector<uint16_t>> *hours)
{
    auto can_visit = [&](int16_t i, int16_t j) {
        char c = island[i][j];
        return c == '@' || c == '.' || c == '!';
    };

    queue<pair<int16_t, int16_t>> q;
    for (auto &row: *hours)
        for (auto &d: row)
            d = numeric_limits<uint16_t>::max();
    (*hours)[start.first][start.second] = 0;

    q.emplace(start);
    while (!q.empty()) {
        pair<int16_t, int16_t> p = q.front();
        q.pop();

        const pair<int16_t, int16_t> next[4] = {
            { max(p.first - 1, 0),                          p.second    },
            { min<int16_t>(p.first + 1, island.size() - 1), p.second    },
            { p.first, max(p.second - 1, 0)                             },
            { p.first, min<int16_t>(p.second + 1, island[0].size() - 1) }
        };

        auto d = (*hours)[p.first][p.second];
        for (const auto &n: next) {
            if (can_visit(n.first, n.second) && d + 1u < (*hours)[n.first][n.second]) {
                (*hours)[n.first][n.second] = d + 1u;
                q.emplace(n.first, n.second);
            }
        }
    }
}

int main()
{
    vector<vector<char>> island;
    vector<pair<int16_t, int16_t>> camps, treasures;

    vector<vector<uint16_t>> hours;
    vector<uint16_t> s_hours;           // hours from the start (landing point)
    vector<vector<uint16_t>> t_hours;   // hours between treasures
    vector<uint16_t> sequence;

    for (int16_t h, w; cin >> h >> w && h > 0; ) {
        camps.clear();
        treasures.clear();
        pair<int16_t, int16_t> start;

        island.resize(h);
        for (int16_t i = 0; i < h; i++) {
            island[i].resize(w + 1);
            cin >> island[i].data();
            for (int16_t j = 0; j < w; j++)
                if (island[i][j] == '*')
                    camps.emplace_back(i, j);
                else if (island[i][j] == '!')
                    treasures.emplace_back(i, j);
                else if (island[i][j] == '@')
                    start = decltype(start)(i, j);
            island[i].resize(w);
        }

        bool is_possible = true;
        for (auto &c: camps)
            for (int16_t i = max(c.first - 1, 0); i < h && i <= c.first + 1; i++)
                for (int16_t j = max(c.second - 1, 0); j < w && j <= c.second + 1; j++)
                    if (island[i][j] == '.')
                        island[i][j] = '*';
                    else if (island[i][j] == '!' || island[i][j] == '@')
                        is_possible = false;

        if (is_possible) {
            hours.resize(h);
            for (auto &hs: hours)
                hs.resize(w);
            traverse(island, start, &hours);

            s_hours.resize(treasures.size());
            for (uint16_t i = 0; i < treasures.size(); i++) {
                const auto &t = treasures[i];
                s_hours[i] = hours[t.first][t.second];
            }
            is_possible = all_of(s_hours.begin(), s_hours.end(),
                                 [=](uint16_t d) { return d < numeric_limits<uint16_t>::max(); });
        }

        if (!is_possible)
            cout << -1 << endl;
        else if (treasures.size() == 0)
            cout << 0 << endl;
        else {
            t_hours.resize(treasures.size());
            for (uint16_t i = 0; i < treasures.size(); i++) {
                t_hours[i].resize(treasures.size());
                traverse(island, treasures[i], &hours);
                for (uint16_t j = 0; j < treasures.size(); j++) {
                    const auto &t = treasures[j];
                    t_hours[i][j] = hours[t.first][t.second];
                }
            }

            sequence.resize(treasures.size());
            iota(sequence.begin(), sequence.end(), 0);

            uint16_t min_hours = numeric_limits<uint16_t>::max();
            do {
                uint16_t hours = s_hours[sequence.front()];
                for (uint16_t i = 0; i + 1u < sequence.size(); i++)
                    hours += t_hours[sequence[i]][sequence[i + 1]];
                hours += s_hours[sequence.back()];
                min_hours = min(min_hours, hours);
            } while (next_permutation(sequence.begin(), sequence.end()));

            cout << min_hours << endl;
        }
    }

    return 0;
}
