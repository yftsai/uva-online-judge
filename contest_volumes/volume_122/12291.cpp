// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void flip_unsafe(uint16_t n, char large[10][11],
          uint16_t row, uint16_t col, const vector<pair<uint16_t, uint16_t>> &small)
{
    for (uint16_t i = 0; i < small.size(); i++) {
        uint16_t r = row + small[i].first;
        uint16_t c = col + small[i].second;
        if (large[r][c] == '*')
            large[r][c] = '.';
        else
            large[r][c] = '*';
    }
}

bool flip(uint16_t n, char large[10][11],
          uint16_t row, uint16_t col, const vector<pair<uint16_t, uint16_t>> &small)
{
    for (uint16_t i = 1; i < small.size(); i++) {
        uint16_t r = row + small[i].first;
        uint16_t c = col + small[i].second;
        if (r >= n || c >= n
            || large[r][c] != large[row + small.front().first][col + small.front().second])
            return false;
    }

    flip_unsafe(n, large, row, col, small);
    return true;
}

typedef pair<uint16_t, uint16_t> pos_t;

pos_t next(uint16_t n, pos_t p)
{
    p.second++;
    if (p.second == n) {
        p.first++;
        p.second = 0;
    }
    return p;
}

bool compose(uint16_t n, char large[10][11], const vector<pair<uint16_t, uint16_t>> &small)
{
    for (pos_t p(0, 0); p.first < n; p = next(n, p))
        if (large[p.first + small.front().first][p.second + small.front().second] == '*'
            && flip(n, large, p.first, p.second, small)) {
            for (pos_t q = next(n, p); q.first < n; q = next(n, q))
                if (large[q.first + small.front().first][q.second + small.front().second] == '*'
                    && flip(n, large, q.first, q.second, small)) {
                    flip_unsafe(n, large, q.first, q.second, small);
                    flip_unsafe(n, large, p.first, p.second, small);
                    return true;
                }
            flip_unsafe(n, large, p.first, p.second, small);
        }
    return false;
}

int main()
{
    char large[10][11], line[11];
    vector<pos_t> small;

    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        uint16_t large_size = 0;
        for (uint16_t i = 0; i < n; i++) {
            cin >> large[i];
            large_size += count(large[i], large[i] + n, '*');
        }

        small.clear();
        for (uint16_t i = 0; i < m && cin >> line; i++)
            for (uint16_t j = 0; j < m; j++)
                if (line[j] == '*')
                    small.emplace_back(i, j);
        pos_t base(m, m);
        for (auto &p: small) {
            base.first = min(p.first, base.first);
            base.second = min(p.second, base.second);
        }
        for (auto &p: small) {
            p.first -= base.first;
            p.second -= base.second;
        }

        cout << ((large_size == small.size() * 2 && compose(n, large, small)) ? 1 : 0) << endl;
    }

    return 0;
}
