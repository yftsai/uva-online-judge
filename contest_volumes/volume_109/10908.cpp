// #dynamic_programming
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    char grid[100][101];
    uint16_t lengths[100][100];

    uint16_t t, m, n, q;
    for (cin >> t; t > 0 && cin >> m >> n >> q; t--) {
        for (uint16_t r = 0; r < m && cin >> grid[r]; r++)
            for (uint16_t c = 0; c < n; c++)
                if (r == 0 || c == 0
                    || grid[r][c] != grid[r - 1][c]
                    || grid[r][c] != grid[r][c - 1]
                    || grid[r][c] != grid[r - 1][c - 1]) {
                    lengths[r][c] = 1;
                }
                else {
                    lengths[r][c] = min(lengths[r - 1][c] + 1, lengths[r][c - 1] + 1);
                    lengths[r][c] = min<uint16_t>(lengths[r - 1][c - 1] + 1, lengths[r][c]);
                }

        cout << m << " " << n << " " << q << endl;
        for (uint16_t i = 0, r, c; i < q && cin >> r >> c; i++) {
            uint16_t length = 1;
            while (++r < m && ++c < n && lengths[r][c] >= length + 2)
                length += 2;
            cout << length << endl;
        }
    }
    return 0;
}
