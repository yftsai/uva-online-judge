// #cycle_detection
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    typedef pair<int16_t, int16_t> vec_t;

    vector<string> grid;
    auto move = [&grid](vec_t &p) {
        switch (grid[p.first][p.second]) {
            case 'N': p.first--;  break;
            case 'E': p.second++; break;
            case 'W': p.second--; break;
            default:  p.first++;  break;
        }
    };

    for (int16_t r, c, e; cin >> r >> c >> e && r > 0; ) {
        auto validate = [r, c](const vec_t &p) {
            return 0 <= p.first  && p.first < r
                && 0 <= p.second && p.second < c;
        };

        grid.resize(r);
        for (auto &row: grid)
            cin >> row;

        const vec_t p(0, e - 1);
        vec_t q = p;
        uint16_t n_steps = 0;
        for (uint16_t i = 0; i < r * c + 1 && validate(q); i++, n_steps++, move(q))
            ;

        if (!validate(q))
            cout << n_steps << " step(s) to exit" << endl;
        else {
            uint16_t n_loop_steps = 0;
            for (vec_t v; grid[q.first][q.second] != 'L'; q = v, n_loop_steps++) {
                v = q;
                move(v);
                grid[q.first][q.second] = 'L';
            }
            for (q = p, n_steps = 0; grid[q.first][q.second] != 'L'; move(q), n_steps++)
                ;
            cout << n_steps << " step(s) before a loop of " << n_loop_steps << " step(s)" << endl;
        }
    }

    return 0;
}
