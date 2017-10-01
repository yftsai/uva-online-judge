// #easy
// The judge input seemed ill-formatted that I got RE with simple I/O in Python.
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    for (cin >> t; t > 0; t--) {
        int board_n, board_m, s;
        cin >> board_n >> board_m >> s;
        char board[51][51];
        for (int i = 0; i < board_n && cin >> board[i]; i++)
            ;

        for (; s > 0; s--) {
            int piece_n, piece_m;
            cin >> piece_n >> piece_m;

            char row[51];
            int pieces[2501][2], piece_count = 0;
            for (int i = 0; i < piece_n && cin >> row; i++)
                for (int j = 0; j < piece_m; j++)
                    if (row[j] == '*') {
                        pieces[piece_count][0] = i;
                        pieces[piece_count][1] = j;
                        piece_count++;
                    }

            int max_row = 0, max_col = 0;
            if (piece_count > 0) {
                int min_row = piece_n, min_col = piece_m;
                for (int i = 0; i < piece_count; i++) {
                    min_row = min(min_row, pieces[i][0]);
                    min_col = min(min_col, pieces[i][1]);
                }
                if (min_row > 0 || min_col > 0)
                    for (int i = 0; i < piece_count; i++) {
                        pieces[i][0] -= min_row;
                        pieces[i][1] -= min_col;
                    }
                for (int i = 0; i < piece_count; i++) {
                    max_row = max(max_row, pieces[i][0]);
                    max_col = max(max_col, pieces[i][1]);
                }
            }

            bool is_fittable = false;
            for (int r = 0; r + max_row < board_n && !is_fittable; r++)
                for (int c = 0; c + max_col < board_m && !is_fittable; c++)
                    is_fittable = all_of(pieces, pieces + piece_count, [&](int p[2]) { return board[ p [0] + r ][ p[1] + c ] == '*'; });
            cout << (is_fittable ? "Yes" : "No") << endl;
        }
        cout << endl;
    }
    return 0;
}
