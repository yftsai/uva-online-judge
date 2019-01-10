// #trivial
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int count(const vector<string> &large_square, const vector<string> &small_square)
{
    const int n(large_square.size()), m(small_square.size());
    int count = 0;
    for (int row = 0; row <= n - m; ++row) {
        for (int col = 0; col <= n - m; ++col) {
            bool is_same = true;
            for (int i = 0; i < m && is_same; ++i)
                is_same = equal(small_square[i].begin(), small_square[i].end(), large_square[row + i].begin() + col);
            if (is_same)
                ++count;
        }
    }
    return count;
}

int main()
{
    vector<string> large_square, small_square, rotated_square;
    for (int n, m; cin >> n >> m && n > 0; ) {
        large_square.resize(n);
        for (string &row: large_square)
            cin >> row;
        small_square.resize(m);
        for (string &row: small_square)
            cin >> row;

        cout << count(large_square, small_square);

        rotated_square.resize(m);
        for (string &row: rotated_square)
            row.resize(m);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < m; ++j)
                for (int k = 0; k < m; ++k)
                    rotated_square[k][m - 1 - j] = small_square[j][k];
            small_square.swap(rotated_square);
            cout << " " << count(large_square, small_square);
        }
        cout << endl;
    }

    return 0;
}
