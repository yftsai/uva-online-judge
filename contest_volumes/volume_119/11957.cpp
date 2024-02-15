// #easy #dynamic_programming
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    char board[100][101];
    unordered_map<int16_t, uint32_t> counts[3];
    constexpr uint32_t m = 1000007;

    uint16_t t;
    cin >> t;
    for (uint16_t cn = 1, n; cn <= t && cin >> n; cn++) {
        for (auto &cs: counts)
            cs.clear();
        int16_t row = 0;
        for (int16_t r = 0; r < n && cin >> board[r]; r++)
            for (int16_t c = 0; c < n; c++)
                if (board[r][c] == 'W') {
                    counts[0][c] = 1;
                    row = r;
                }

        for (; row > 0; row--) {
            for (const auto &cc: counts[0]) {
                pair<int16_t, int16_t> p(row, cc.first);
                if (0 <= --p.second && board[--p.first][p.second] == '.')
                    counts[1][p.second] = (counts[1][p.second] + cc.second) % m;
                else if (0 <= --p.first && 0 <= --p.second && board[p.first][p.second] == '.')
                    counts[2][p.second] = (counts[2][p.second] + cc.second) % m;

                p = pair<int16_t, int16_t>(row, cc.first);
                if (++p.second < n && board[--p.first][p.second] == '.')
                    counts[1][p.second] = (counts[1][p.second] + cc.second) % m;
                else if (0 <= --p.first && ++p.second < n && board[p.first][p.second] == '.')
                    counts[2][p.second] = (counts[2][p.second] + cc.second) % m;
            }
            counts[0].swap(counts[1]);
            counts[1].swap(counts[2]);
            counts[2].clear();
        }

        uint32_t count = 0;
        for (const auto &cc: counts[0])
            count = (count + cc.second) % m;
        cout << "Case " << cn << ": " << count << endl;
    }
    return 0;
}
