// #breadth-first_search
#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>
#include <numeric>
using namespace std;

void do_along_edge(pair<int, int> s, pair<int, int> t, function<void(int, int)> action)
{
    if (s.first == t.first)
        for (int j = min(s.second, t.second); j <= max(s.second, t.second); j++)
            action(s.first, j);
    else
        for (int j = min(s.first, t.first); j <= max(s.first, t.first); j++)
            action(j, s.second);
}

int main()
{
    const uint16_t destination = numeric_limits<uint16_t>::max();
    const uint16_t max_distance = destination - 1;
    uint16_t city[2001][2001];
    for (int r = 0; r <= 2000; r++)
        for (int c = 0; c <= 2000; c++)
            city[r][c] = max_distance;

    for (int p; cin >> p && p > 0;) {
        pair<int, int> row_limits(2000, 0), col_limits(2000, 0);
        auto update_boundaries = [&](int r, int c) {
            row_limits = make_pair(min(row_limits.first, r), max(row_limits.second, r));
            col_limits = make_pair(min(col_limits.first, c), max(col_limits.second, c));
        };

        pair<int, int> start, s, t;
        auto set_destination = [&](int r, int c) {  city[r][c] = destination; };
        for (int i = 0; i < p && cin >> t.first >> t.second; i++, swap(s, t)) {
            update_boundaries(t.first, t.second);
            if (i == 0)
                start = t;
            else if (i < p - 1)
                do_along_edge(s, t, set_destination);
            else {
                do_along_edge(s, t, set_destination);
                do_along_edge(t, start, set_destination);
            }
        }

        cin >> p;
        queue<pair<int, int>> q;
        auto enqueue = [&](int r, int c) {
            q.push(pair<int, int>(r, c));
            city[r][c] = 0;
        };
        for (int i = 0; i < p && cin >> t.first >> t.second; i++, swap(s, t)) {
            update_boundaries(t.first, t.second);
            if (i == 0)
                start = t;
            else if (i < p - 1)
                do_along_edge(s, t, enqueue);
            else {
                do_along_edge(s, t, enqueue);
                do_along_edge(t, start, enqueue);
            }
        }

        // BFS
        uint16_t min_distance = max_distance;
        auto explore = [&](int r, int c, int d) {
            if (row_limits.first <= r && r <= row_limits.second
                && col_limits.first <= c && c <= col_limits.second) {
                if (city[r][c] == destination)
                    min_distance = d;
                else if (city[r][c] > d) {
                    city[r][c] = d;
                    q.push(pair<int, int>(r, c));
                }
            }
        };
        while (min_distance == max_distance) {
            int r = q.front().first, c = q.front().second;
            q.pop();
            explore(r - 1, c, city[r][c] + 1);
            explore(r + 1, c, city[r][c] + 1);
            explore(r, c - 1, city[r][c] + 1);
            explore(r, c + 1, city[r][c] + 1);
        }
        cout << min_distance << endl;

        // reset
        for (int r = row_limits.first; r <= row_limits.second; r++)
            for (int c = col_limits.first; c <= col_limits.second; c++)
                city[r][c] = max_distance;
    }
    return 0;
}
