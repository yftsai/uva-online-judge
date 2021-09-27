// #dynamic_programming
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    uint32_t n, q;
    cin >> n >> q;

    vector<vector<uint32_t>> min_vals(1);
    min_vals.front().resize(n);
    for (auto &v: min_vals.front())
        cin >> v;

    auto is_valid = [&](uint16_t row, uint32_t i) {
        return row < min_vals.size() && i < min_vals[row].size();
    };
    auto get_min = [&](const uint16_t row, const uint32_t i) {
        return min(min_vals[row - 1][i * 2], min_vals[row - 1][i * 2 + 1]);
    };

    for (uint16_t row = 0; min_vals[row].size() > 1; row++) {
        min_vals.emplace_back(min_vals[row].size() / 2);
        for (uint32_t i = 0; i < min_vals[row + 1].size(); i++)
            min_vals[row + 1][i] = get_min(row + 1, i);
    }

    vector<uint32_t> indexes;
    for (string line; cin >> line; ) {
        stringstream ss(line.c_str() + 6);
        char sep;

        if (line[0] == 'q') {
            uint32_t i, j, row = 0;
            ss >> i >> sep >> j;

            uint32_t min_val = min_vals[row][--i];
            for (; i < j; row++, i /= 2, j /= 2) {
                if (i % 2 == 1)
                    min_val = min(min_vals[row][i++], min_val);
                if (j % 2 == 1)
                    min_val = min(min_vals[row][--j], min_val);
            }
            cout << min_val << endl;
        }
        else {
            indexes.clear();
            for (uint32_t v; ss >> v >> sep; )
                indexes.push_back(v - 1);

            auto &front = min_vals.front();
            for (uint32_t i = 0; i + 1 < indexes.size(); i++)
                swap(front[ indexes[i] ], front[ indexes[i + 1] ]);

            for (const uint32_t i: indexes)
                for (uint32_t r = 1, j = i / 2; is_valid(r, j) && min_vals[r][j] != get_min(r, j); r++, j /= 2)
                    min_vals[r][j] = get_min(r, j);
        }
    }

    return 0;
}
