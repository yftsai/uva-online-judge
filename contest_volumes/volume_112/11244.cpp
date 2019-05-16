// #trivial
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool is_star(const vector<string> &sky, int16_t r, int16_t c)
{
    if (sky[r][c] != '*')
        return false;
    else {
        uint16_t count = 0;
        for (int16_t i = max<int16_t>(0, r - 1); i < min<int16_t>(r + 2, sky.size()); ++i)
            for (int16_t j = max<int16_t>(0, c - 1); j < min<int16_t>(c + 2, sky[i].size()); ++j)
                count += (sky[i][j] == '*') ? 1 : 0;
        return count == 1;
    }
}

int main()
{
    vector<string> sky;
    for (int16_t r, c; cin >> r >> c && r > 0; ) {
        sky.resize(r);
        for (auto &row: sky)
            cin >> row;

        uint16_t count = 0;
        for (int16_t i = 0; i < r; ++i)
            for (int16_t j = 0; j < c; ++j)
                if (is_star(sky, i, j))
                    ++count;
        cout << count << endl;
    }
    return 0;
}
