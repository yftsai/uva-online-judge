// #easy
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    constexpr char visited_grid = '#';
    auto is_alive_ship = [](char g) { return g == 'x'; };
    auto is_ship = [](char g) { return g == 'x' || g == '@'; };

    vector<string> grids;

    uint16_t t;
    cin >> t;
    for (uint16_t number = 1, n; number <= t && cin >> n; ++number) {
        grids.resize(n);
        for (string &row: grids)
            cin >> row;

        uint16_t alive_count = 0;
        for (uint16_t r = 0; r < n; ++r)
            for (uint16_t c = 0; c < n; ++c)
                if (is_ship(grids[r][c])) {
                    bool is_alive = false;
                    for (uint16_t s = r; s < n && is_ship(grids[s][c]); ++s) {
                       is_alive = is_alive || is_alive_ship(grids[s][c]);
                       grids[s][c] = visited_grid;
                    }
                    for (uint16_t d = c + 1; d < n && is_ship(grids[r][d]); ++d) {
                        is_alive = is_alive || is_alive_ship(grids[r][d]);
                        grids[r][d] = visited_grid;
                    }

                    alive_count += is_alive ? 1 : 0;
                }

        cout << "Case " << number << ": " << alive_count << endl;
    }

    return 0;
}
