// #easy
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <vector>
#include <array>
#include <functional>
using namespace std;

int main()
{
    vector<array<int, 8>> valid_boards;
    array<int, 8> board;

    iota(board.begin(), board.end(), 1);
    do {
        bool is_valid = true;
        int i;
        for (i = 1; i < 8 && is_valid; ++i)
            for (int j = 0; j < i && is_valid; ++j)
                is_valid = (abs(board[i] - board[j]) != abs(i - j));
        if (is_valid)
            valid_boards.push_back(board);
        else if (i < 8)
            sort(board.begin() + i + 1, board.end(), greater<int>());
    } while (next_permutation(board.begin(), board.end()));

    for (int case_number = 1; cin >> board.front(); ++case_number) {
        for (int i = 1; i < 8; ++i)
            cin >> board[i];

        int moves = 8;
        for (const auto &valid_board: valid_boards) {
            int m = 0;
            for (int i = 0; i < 8; ++i)
                if (board[i] != valid_board[i])
                    ++m;
            moves = min(moves, m);
        }
        cout << "Case " << case_number << ": " << moves << endl;
    }

    return 0;
}
