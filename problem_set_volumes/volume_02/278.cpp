// #n_queen
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int get_max_rooks(int m, int n)
{
    return min(m, n);
}

int get_max_knights(int m, int n)
{
    return (m * n + 1) / 2;
}

int get_max_queens(int m, int n)
{
    if (m > n)
        swap(m, n);

    for (int queen_count = m; queen_count > 0; --queen_count) {
        bool is_selected[n];
        fill(is_selected, is_selected + n - queen_count, false);
        fill(is_selected + n - queen_count, is_selected + n, true);
        do {
            int cols[m];
            for (int i = 0, j = 0; i < n; ++i)
                if (is_selected[i])
                    cols[j++] = i;
            fill(cols + queen_count, cols + m, n);

            do {
                bool is_valid = true;
                for (int i = 1; i < m && is_valid; ++i)
                    for (int j = 0; j < i && cols[i] < n && is_valid; ++j)
                        is_valid = (cols[j] == n || abs(cols[i] - cols[j]) != (i - j));
                if (is_valid)
                    return queen_count;
            } while (next_permutation(cols, cols + m));
        } while (next_permutation(is_selected, is_selected + n));
    }

    return 0;
}

int get_max_kings(int m, int n)
{
    return (m + 1) / 2 * ((n + 1) / 2);
}

int main()
{
    int count;
    for (cin >> count; count > 0; --count) {
        char chesspiece;
        int m, n;
        cin >> chesspiece >> m >> n;

        if (chesspiece == 'r')
            cout << get_max_rooks(m, n) << endl;
        else if (chesspiece == 'k')
            cout << get_max_knights(m, n) << endl;
        else if (chesspiece == 'Q')
            cout << get_max_queens(m, n) << endl;
        else
            cout << get_max_kings(m, n) << endl;
    }

    return 0;
}
