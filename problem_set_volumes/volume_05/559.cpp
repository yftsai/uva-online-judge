// #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_expandable(const vector<vector<int16_t>> &board, uint16_t r, uint16_t c, uint16_t i)
{
    if (r + i - 1u >= board.size() || c + i - 1u >= board[r + i - 1].size())
        return false;
    else {
        for (uint16_t j = c; j <= c + i; ++j)
            if (board[r + i - 1][j - 1] == 0)
                return false;
        for (uint16_t j = r; j + 1 <= r + i; ++j)
            if (board[j - 1][c + i - 1] == 0)
                return false;
        return true;
    }
}

int main()
{
    vector<vector<int16_t>> board(1000);
    for (auto &row: board)
        row.reserve(1000);

    uint32_t g;
    uint16_t h, w, m;
    for (cin >> g; g > 0 && cin >> h >> w >> m; --g) {
        board.resize(h);
        for (auto &row: board)
            row.assign(w, 1);
        for (uint16_t i = 0, r, c; i < m && cin >> r >> c; ++i)
            for (uint16_t j = 0; is_expandable(board, r, c, j); ++j)
                for (uint16_t k = 0; k <= j; ++k)
                    board[r + k - 1][c + j - 1] = board[r + j - 1][c + k - 1] = 0;

        int16_t r = -1, c = -1, s = 0;
        auto update = [&](uint16_t i, uint16_t j) {
            if (board[i][j] > s) {
                r = i;
                c = j;
                s = board[i][j];
            }
        };

        for (uint16_t j = 0; j < w && s == 0; ++j)
            update(0, j);

        for (uint16_t i = 1; i < h; ++i) {
            update(i, 0);
            for (uint16_t j = 1; j < w; ++j)
                if (board[i][j] != 0) {
                    board[i][j] = min(min(board[i - 1][j], board[i][j - 1]), board[i - 1][j - 1]) + 1;
                    update(i, j);
                }
        }

        if (s == 0)
            cout << "game over" << endl;
        else
            cout << (r - s + 2) << " " << (c - s + 2) << " " << s << endl;
    }

    return 0;
}
