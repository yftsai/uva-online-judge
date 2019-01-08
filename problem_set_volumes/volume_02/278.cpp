// #nqueen
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

int get_max_queens(int m, int n, int cols[10], int index = 0)
{
    int count = 0;
    if (index == m) {
        for (int i = 0; i < m; ++i)
            if (cols[i] < n)
                count++;
    }
    else {
        for (cols[index] = 0; cols[index] <= n; ++cols[index]) {
            bool is_valid = true;
            for (int i = 0; i < index && is_valid; i++)
                is_valid = (cols[i] == n) || ((cols[i] != cols[index]) && (abs(cols[i] - cols[index]) != (index - i)));
            if (is_valid)
                count = max(count, get_max_queens(m, n, cols, index + 1));
        }
    }

    return count;
}

int get_max_queens(int m, int n)
{
    int cols[10];
    fill(cols, cols + m, n);
    return get_max_queens(m, n, cols, 0);
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
