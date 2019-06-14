// #easy
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
    char arena[100][101];
    const array<char, 4> orientations = {'N', 'L', 'S', 'O'};
    for (uint16_t n, m, s; cin >> n >> m >> s && n > 0; ) {
        pair<uint16_t, uint16_t> p;
        for (uint16_t r = 0; r < n; ++r) {
            cin >> arena[r];
            for (uint16_t c = 0; c < m; ++c)
                if (find(orientations.begin(), orientations.end(), arena[r][c]) != orientations.end())
                    p = pair<uint16_t, uint16_t>(r, c);
        }

        uint16_t count  = 0;
        for (char inst; s > 0 && cin >> inst; --s) {
            if (inst == 'D') {
                uint16_t i = find(orientations.begin(), orientations.end(), arena[p.first][p.second])
                             - orientations.begin();
                arena[p.first][p.second] = orientations[(i + 1u) % orientations.size()];
            }
            else if (inst == 'E') {
                uint16_t i = find(orientations.begin(), orientations.end(), arena[p.first][p.second])
                             - orientations.begin();
                arena[p.first][p.second] = orientations[(i + orientations.size() - 1u) % orientations.size()];
            }
            else {
                pair<uint16_t, uint16_t> q = p;
                if (arena[q.first][q.second] == 'N' && q.first > 0)
                    --q.first;
                else if (arena[q.first][q.second] == 'S' && q.first + 1u < n)
                    ++q.first;
                else if (arena[q.first][q.second] == 'L' && q.second + 1u < m)
                    ++q.second;
                else if (arena[q.first][q.second] == 'O' && q.second > 0)
                    --q.second;
                count += (arena[q.first][q.second] == '*') ? 1 : 0;

                if (arena[q.first][q.second] == '.'
                    || arena[q.first][q.second] == '*') {
                    arena[q.first][q.second] = arena[p.first][p.second];
                    arena[p.first][p.second] = '.';
                    p = q;
                }
            }
        }
        cout << count << endl;
    }

    return 0;
}
