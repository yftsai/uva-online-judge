// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int32_t get_count(
    const uint16_t pos,
    const uint16_t l, const uint16_t s,
    vector<vector<vector<int>>> &counts)
{
    if (l > 26 - pos || s < (pos + 1) * l || s > 26 * l)
        return 0;
    else if (pos == 26)
        return (l == 0 && s == 0) ? 1 : 0;
    else if (l == 0)
        return (s == 0) ? 1 : 0;
    else {
        if (l - 1u >= counts[pos].size())
            counts[pos].resize(l);
        if (s - 1u >= counts[pos][l - 1].size())
            counts[pos][l - 1].resize(s, -1);
        if (counts[pos][l - 1][s - 1] < 0) {
            counts[pos][l - 1][s - 1] = 0;
            for (uint16_t p = pos; p < 26 && p + 1 <= s; ++p)
                counts[pos][l - 1][s - 1] += get_count(p + 1, l - 1, s - p - 1, counts);
        }
        return counts[pos][l - 1][s - 1];
    }
}

int main()
{
    vector<vector<vector<int32_t>>> counts(26);

    uint32_t number = 1;
    for (uint16_t l, s; cin >> l >> s && l != 0; ++number)
        cout << "Case " << number << ": " << get_count(0, l, s, counts) << endl;

    return 0;
}
