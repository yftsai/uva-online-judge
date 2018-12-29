// #dynamic_programming
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
using namespace std;

int to_value(char c)
{
    if ('1' <= c && c <= '9')
        return c - '0';
    else
        return c - 'A' + 10;
}

int main()
{
    unique_ptr<uint64_t[]> counts[2];
    for (auto &cs: counts)
        cs.reset(new uint64_t[16]);

    for (string board; cin >> board; ) {
        const int n(board.size());

        fill(counts[0].get(), counts[0].get() + board.size(), (board[0] == '?') ? 1 : 0);
        if (board[0] != '?')
            counts[0][to_value(board[0]) - 1] = 1;

        for (int i = 1; i < n; ++i, swap(counts[0], counts[1])) {
            if (board[i] == '?') {
                counts[1][0] = accumulate(counts[0].get() + min(2, n), counts[0].get() + n, uint64_t(0));
                for (int j = 1; j < n; ++j)
                    counts[1][j] = counts[1][j - 1] + ((0 <= j - 2) ? counts[0][j - 2] : 0) - ((j + 1 < n) ? counts[0][j + 1] : 0);
            }
            else {
                fill(counts[1].get(), counts[1].get() + board.size(), 0);
                const int r(to_value(board[i]) - 1);
                counts[1][r] = accumulate(counts[0].get(), counts[0].get() + n, uint64_t(0));
                counts[1][r] -= accumulate(counts[0].get() + max(0, r - 1), counts[0].get() + min(n, r + 2), uint64_t(0));
            }
        }
        cout << accumulate(counts[0].get(), counts[0].get() + n, uint64_t(0)) << endl;
    }

    return 0;
}
