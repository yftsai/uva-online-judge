// #n_queen
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <numeric>
using namespace std;

constexpr uint16_t max_n = 16;

uint32_t count_placements(
    const bitset<max_n> is_bad[max_n],
    const int16_t n,
    int16_t queen_cols[max_n],
    const int16_t index)
{
    if (index >= n)
        return 1;
    else {
        uint32_t count = 0;

        bitset<max_n> is_attacked;
        for (uint16_t j = 0; j < index; ++j) {
            int16_t c = queen_cols[j] + j - index;
            if (0 <= c && c < n)
                is_attacked.set(c);
            c = queen_cols[j] - j + index;
            if (0 <= c && c < n)
                is_attacked.set(c);
        }

        for (uint16_t i = index; i < n; ++i)
            if (!is_bad[index][ queen_cols[i] ] && !is_attacked[ queen_cols[i] ]) {
                swap(queen_cols[index], queen_cols[i]);
                count += count_placements(is_bad, n, queen_cols, index + 1);
                swap(queen_cols[index], queen_cols[i]);
            }
        return count;
    }
}

int main()
{
    bitset<max_n> is_bad[max_n];
    int16_t n, queen_cols[max_n];
    string line;
    for (int case_number = 1; cin >> n && n != 0; case_number++) {
        for (int16_t r = 0; r < n && cin >> line; ++r) {
            is_bad[r].reset();
            for (uint16_t c = 0; c < n; ++c)
                if (line[c] == '*')
                    is_bad[r].set(c);
        }

        iota(queen_cols, queen_cols + n, 0);
        cout << "Case " << case_number << ": " << count_placements(is_bad, int16_t(n), queen_cols, 0) << endl;
    }

    return 0;
}
