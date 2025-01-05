// #breadth_first_search
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

int main()
{
    typedef pair<int16_t, int16_t> vec_t;
    const vec_t dirs[8] = {
        vec_t(-1, 0), vec_t(-1, 1), vec_t(0, 1),
        vec_t(1, 1),  vec_t(1, 0),  vec_t(1, -1),
        vec_t(0, -1), vec_t(-1, -1)
    };

    uint16_t r, c;
    cin >> r >> c;
    auto validate = [r, c](vec_t &loc) {
        return 0 <= loc.first  && loc.first  < r
            && 0 <= loc.second && loc.second < c;
    };

    vector<string> lake;
    lake.resize(r);
    for (auto &row: lake)
        cin >> row;

    vector<vector<uint32_t>> energies(r);
    auto energy = [&energies](vec_t &loc) -> uint32_t& {
        return energies[loc.first][loc.second];
    };

    vector<vec_t> q, q_n;
    auto free_move = [&](vec_t loc, uint32_t e) {
        while (validate(loc) && energy(loc) > e) {
            energy(loc) = e;
            q_n.push_back(loc);

            auto d = lake[loc.first][loc.second] - '0';
            loc = vec_t(loc.first + dirs[d].first, loc.second + dirs[d].second);
        }
    };

    uint16_t n, rs, cs, rd, cd;
    for (cin >> n; n > 0 && cin >> rs >> cs >> rd >> cd; n--) {
        for (auto &es: energies) {
            es.clear();
            es.resize(c, numeric_limits<uint32_t>::max());
        }

        free_move(vec_t(rs - 1, cs - 1), 0);
        q.swap(q_n);

        while (energies[rd - 1][cd - 1] == numeric_limits<uint32_t>::max()) {
            for (auto &loc: q)
                for (auto &dir: dirs) {
                    vec_t loc_m(loc.first + dir.first, loc.second + dir.second);
                    free_move(loc_m, energy(loc) + 1);
                }
            q.swap(q_n);
            q_n.clear();
        }
        q.clear();

        cout << energies[rd - 1][cd - 1] << endl;
    }

    return 0;
}
