// #easy
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const array<pair<int8_t, int8_t>, 4> dirs{ {{0, -1}, {0, 1}, {-1, 0}, {1, 0}} };
    vector<vector<uint16_t>> land, updated_land;

    for (uint16_t n, r, c, k; cin >> n >> r >> c >> k && n > 0; ) {
        land.resize(r);
        updated_land.resize(r);
        for (uint16_t i = 0; i < r; i++) {
            land[i].resize(c);
            updated_land[i].resize(c);
            for (uint16_t j = 0; j < c; j++)
                cin >> land[i][j];
        }

        for (uint16_t b = 0; b < k; b++) {
            for (int16_t i = 0; i < r; i++)
                for (int16_t j = 0; j < c; j++) {
                    auto it = find_if(dirs.begin(), dirs.end(),
                        [&](const pair<int8_t, int8_t> &d) {
                            return 0 <= i + d.first  && i + d.first  < r
                                && 0 <= j + d.second && j + d.second < c
                                && land[i][j] == (land[i + d.first][j + d.second] + 1) % n; });
                    if (it != dirs.end())
                        updated_land[i][j] = land[i + it->first][j + it->second];
                    else
                        updated_land[i][j] = land[i][j];
                }
            land.swap(updated_land);
        }

        for (uint16_t i = 0; i < r; i++) {
            cout << land[i][0];
            for (uint16_t j = 1; j < c; j++)
                cout << ' ' << land[i][j];
            cout << endl;
        }
    }

    return 0;
}
