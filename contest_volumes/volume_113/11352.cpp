// #esay #breadth_first_search
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    uint16_t t, m, n;
    string row, board;
    vector<vector<bool>> visited;

    for (cin >> t; t > 0 && cin >> m >> n; t--) {
        board.clear();
        for (uint16_t r = 0; r < m && cin >> row; r++)
            board += row;

        typedef pair<int16_t, int16_t> position;
        auto is_valid = [m, n](const position &p) {
            return 0 <= p.first && p.first < m
                && 0 <= p.second && p.second < n;
        };
        auto get_index = [&](const position &p) { return n * p.first + p.second; };
        const char ATTACKED = 'Y';
        const pair<int16_t, int16_t> horse_moves[] = {
            { -2, -1 }, { -2, 1 },
            { -1, -2 }, { -1, 2 },
            { 1, -2 }, { 1, 2 },
            { 2, -1 }, { 2, 1}
        };
        const pair<int16_t, int16_t> king_moves[] = {
            { -1, -1 }, { -1, 0 }, { -1, 1 },
            { 0, -1 }, { 0, 1 },
            { 1, -1 }, { 1, 0 }, { 1, 1 }
        };

        position pos;
        for (position p(0, 0); p.first < m; p.first++)
            for (p.second = 0; p.second < n; p.second++)
                if (board[get_index(p)] == 'Z')
                    for (const auto &o: horse_moves) {
                        const position q(p.first + o.first, p.second + o.second);
                        if (is_valid(q) && board[get_index(q)] == '.')
                            board[get_index(q)] = ATTACKED;
                    }
                else if (board[get_index(p)] == 'A')
                    pos = p;

        visited.resize(m);
        for (auto &row: visited)
            row.assign(n, false);
        queue<pair<uint32_t, position>> q;
        visited[pos.first][pos.second] = true;
        q.emplace(0, pos);

        while (!q.empty() && board[get_index(q.front().second)] != 'B') {
            const auto step_count = q.front().first;
            pos = q.front().second;
            q.pop();

            for (const auto &o: king_moves) {
                const position r(pos.first + o.first, pos.second + o.second);
                if (is_valid(r)
                    && (board[get_index(r)] == '.' || board[get_index(r)] == 'B')
                    && !visited[r.first][r.second]) {
                        visited[r.first][r.second] = true;
                        q.emplace(step_count + 1, r);
                    }
            }
        }

        if (!q.empty())
            cout << "Minimal possible length of a trip is " << q.front().first << endl;
        else
            cout << "King Peter, you can't go now!" << endl;
    }

    return 0;
}
