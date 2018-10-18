// #easy
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef pair<int16_t, int16_t> position;

int main()
{
    string name;
    uint16_t n, r, c, heights[100][100], lengths[100][100];
    position positions[100 * 100];
    for (cin >> n; n > 0 && cin >> name >> r >> c; n--) {
        for (uint16_t i = 0; i < r; i++)
            for (uint16_t j = 0; j < c; j++) {
                cin >> heights[i][j];
                position &p = positions[c * i + j];
                p.first = i;
                p.second = j;
                lengths[i][j] = 1;
            }

        auto by_heights = [&heights](const position &p, const position &q) {
            return heights[p.first][p.second] < heights[q.first][q.second];
        };
        sort(positions, positions + r * c, by_heights);

        uint16_t longest_length = 0;
        for (int i = 0; i < r * c; i++) {
            const position &p = positions[i];
            const pair<int, int> neighbors[] = {
                make_pair(max(0, p.first - 1), p.second),
                make_pair(min(p.first + 1, r - 1), p.second),
                make_pair(p.first, max(p.second - 1, 0)),
                make_pair(p.first, min(p.second + 1, c - 1)) };
            uint16_t &h = heights[p.first][p.second], &len = lengths[p.first][p.second];
            for (auto &n: neighbors)
                if (h > heights[n.first][n.second])
                    len = max(len, uint16_t(lengths[n.first][n.second] + 1));
            longest_length = max(longest_length, len);
        }
        cout << name << ": " << longest_length << endl;
    }

    return 0;
}
