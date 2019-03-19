// #minmax
#include <iostream>
#include <string>
#include <map>
using namespace std;

char get_row_winner(const string &board, uint16_t p)
{
    const uint16_t row = p / 4;
    uint16_t c = 0;
    for (c = 0; c < 4 && board[4 * row + c] == board[p]; ++c)
        ;
    return (c == 4) ? board[p] : '.';
}

char get_col_winner(const string &board, uint16_t p)
{
    const uint16_t col = p % 4;
    uint16_t r = 0;
    for (r = 0; r < 4 && board[4 * r + col] == board[p]; ++r)
        ;
    return (r == 4) ? board[p] : '.';
}

char get_winner(const string &board, uint16_t p)
{
    char w = board[0];
    for (uint16_t i = 1; i < 4 && w != '.'; ++i)
        w = (w == board[4 * i + i]) ? w : '.';
    if (w != '.')
        return w;

    w = board[3];
    for (uint16_t i = 1; i < 4 && w != '.'; ++i)
        w = (w == board[4 * i + 3 - i]) ? w : '.';
    if (w != '.')
        return w;

    w = get_row_winner(board, p);
    if (w != '.')
        return w;

    return get_col_winner(board, p);
}

uint16_t play(char player, string &board, map<string, uint16_t> &verdict)
{
    auto it = verdict.lower_bound(board);
    if (it == verdict.end() || it->first != board) {
        uint16_t win_pos = 16;
        for (uint16_t p = 0; p < win_pos; ++p)
            if (board[p] == '.') {
                board[p] = player;
                if (get_winner(board, p) == player
                    || play((player == 'x') ? 'o' : 'x', board, verdict) >= 16)
                    win_pos = p;
                board[p] = '.';
            }
        it = verdict.emplace_hint(it, board, win_pos);
    }
    return it->second;
}

int main()
{
    string row, board;
    for (char mark; cin >> mark && mark == '?'; ) {
        board.clear();
        for (int r = 0; r < 4 && cin >> row; ++r)
            board += row;

        bool is_over = (get_winner(board, 0) != '.');
        for (uint16_t i = 0; i < 4 && !is_over; ++i)
            is_over = (get_col_winner(board, i) != '.' || get_row_winner(board, 4 * i) != '.');

        map<string, uint16_t> verdict;
        uint16_t p = play('x', board, verdict);
        if (p < 16)
            cout << "(" << (p / 4) << "," << (p % 4) << ")" << endl;
        else
            cout << "#####" << endl;
    }

    return 0;
}
