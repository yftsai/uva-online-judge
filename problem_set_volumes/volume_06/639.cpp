// #easy #n_queen
#include <iostream>
#include <vector>
#include <string>
using namespace std;

uint16_t get_max_rook_count(vector<string> &board, uint16_t count = 0, uint16_t pos = 0)
{
    const uint16_t n = board.size();
    auto get = [&](uint16_t p) -> char & {
        return board[p / n][p % n];
    };

    while (pos < n * n && get(pos) == 'X')
        ++pos;

    constexpr char rook = 'R';
    uint16_t max_count = count;
    if (pos < n * n) {
        bool is_valid = true;
        for (uint16_t p = pos; p % n > 0 && get(p - 1) != 'X' && is_valid; --p) {
            is_valid = (get(p - 1) != rook);
        }
        for (uint16_t p = pos; p >= n && get(p - n) != 'X' && is_valid; p -= n)
            is_valid = (get(p - n) != rook);
        if (is_valid) {
            char r = rook;
            swap(r, get(pos));
            max_count = max(max_count, get_max_rook_count(board, count + 1, pos + 1));
            swap(r, get(pos));
        }
        max_count = max(max_count, get_max_rook_count(board, count, pos + 1));
    }

    return max_count;
}

int main()
{
    vector<string> board;
    for (uint16_t n; cin >> n && n != 0; ) {
        board.resize(n);
        for (string &row: board)
            cin >> row;
        cout << get_max_rook_count(board) << endl;
    }

    return 0;
}
