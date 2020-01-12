// #dynamic_programming
// Some input value is likely larger than the description.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

uint16_t get_cycle_length(uint32_t n, vector<uint16_t> &lengths)
{
    uint16_t len;
    if (n < lengths.size() && lengths[n] != 0)
        len = lengths[n];
    else {
        if (n % 2 == 1)
            len = get_cycle_length(3 * n + 1, lengths) + 1;
        else
            len = get_cycle_length(n / 2, lengths) + 1;

        if (n < lengths.size())
            lengths[n] = len;
    }
    return len;
}

uint16_t get_max_length(uint16_t e, uint32_t i, uint32_t j, vector<vector<uint16_t>> &lengths)
{
    if (e >= lengths.size())
        lengths.resize(e + 1u);
    if (j >= lengths[e].size())
        lengths[e].resize(j + 1u, 0);

    if (i == j) {
        if (lengths[e][i] == 0 && e == 0)
            get_cycle_length(i, lengths[0]);
        else if (lengths[e][i] == 0)
            lengths[e][i] = max(get_max_length(e - 1, i * 2,     i * 2,     lengths),
                                get_max_length(e - 1, i * 2 + 1, i * 2 + 1, lengths));
        return lengths[e][i];
    }
    else if (i % 2 == 1)
        return max(get_max_length(e, i, i, lengths), get_max_length(e, i + 1, j, lengths));
    else if (j % 2 == 0)
        return max(get_max_length(e, i, j - 1, lengths), get_max_length(e, j, j, lengths));
    else
        return get_max_length(e + 1, i / 2, j / 2, lengths);
}

int main()
{
    vector<vector<uint16_t>> lengths(1);
    lengths[0].assign(2, 1);

    for (uint32_t i, j; cin >> i >> j; )
        cout << i << " " << j << " " << get_max_length(0, min(i, j), max(i, j), lengths) << endl;

    return 0;
}
