// #set_union
// The flights is implicitly bidirectional.
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
using namespace std;

int main()
{
    constexpr uint16_t size = 26;
    array<uint16_t, size> connections[2];
    array<uint16_t, size> matching[2];
    auto get_set = [&](uint16_t i, uint16_t j) {
        uint16_t r = j;
        while (connections[i][r] != r)
            r = connections[i][r];
        for (uint16_t k; (k = connections[i][j]) != r; j = k)
            connections[i][j] = r;
        return r;
    };

    uint32_t tcount;
    for (cin >> tcount; tcount > 0; tcount--) {
        for (uint32_t i = 0, n; i < 2 && cin >> n; i++) {
            iota(connections[i].begin(), connections[i].end(), 0);

            char a, b;
            for (uint32_t j = 0; j < n && cin >> a >> b; j++) {
                uint16_t c = get_set(i, a - 'A');
                uint16_t d = get_set(i, b - 'A');
                connections[i][c] = d;
            }
        }

        for (uint16_t i = 0; i < 2; i++)
            matching[i].fill(size);
        bool is_equal = true;
        for (uint16_t i = 0; i < matching[0].size() && is_equal; i++) {
            uint16_t s = get_set(0, i);
            uint16_t t = get_set(1, i);
            if (matching[0][s] == size && matching[1][t] == size) {
                matching[0][s] = t;
                matching[1][t] = s;
            }
            else {
                is_equal = (matching[0][s] == t && matching[1][t] == s);
            }
        }

        cout << (is_equal ? "YES" : "NO") << endl;
        if (tcount > 1)
            cout << endl;
    }

    return 0;
}
