// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

uint16_t verify(
    const vector<vector<uint16_t>> &says_reliable,
    const vector<vector<uint16_t>> &says_unreliable,
    const vector<bool> &is_reliable)
{
    uint16_t i;
    for (i = 0; i < is_reliable.size(); i++)
        if (is_reliable[i]) {
            for (auto j: says_reliable[i])
                if (!is_reliable[j])
                    return max(i, j);
            for (auto j: says_unreliable[i])
                if (is_reliable[j])
                    return max(i, j);
        }
    return i;
}

int main()
{
    vector<vector<uint16_t>> says_reliable, says_unreliable;
    vector<bool> is_reliable;

    for (int16_t i, a; cin >> i >> a && i > 0; ) {
        says_reliable.clear();
        says_reliable.resize(i);
        says_unreliable.clear();
        says_unreliable.resize(i);

        for (int16_t j = 0, x, y; j < a && cin >> x >> y; j++) {
            if (y < 0)
                says_unreliable[x - 1].push_back(-y - 1);
            else
                says_reliable[x - 1].push_back(y - 1);
        }

        uint16_t n, v;
        for (n = i, v = 0; n > 0 && v < i; n--) {
            is_reliable.clear();
            is_reliable.resize(i - n, false);
            is_reliable.resize(    i, true);

            do {
                v = verify(says_reliable, says_unreliable, is_reliable);
                for (uint16_t u = v + 1, w = i; u < w; u++, w--) {
                    while (u < w && is_reliable[u])
                        u++;
                    while (u < w && !is_reliable[w - 1])
                        w--;
                    if (u < w)
                        swap(is_reliable[u], is_reliable[w - 1]);
                }
            } while (v < i && next_permutation(is_reliable.begin(), is_reliable.end()));
        }
        cout << ((v == i) ? n + 1 : 0) << endl;
    }

    return 0;
}
