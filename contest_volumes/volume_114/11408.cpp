// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    constexpr uint32_t max_n = 5000000;
    vector<uint32_t> sums(max_n + 1, 1);

    // set sums[v] as p if p is a prime factor of v
    for (uint32_t q = 4; q < sums.size(); q += 2)
        sums[q] = 2;
    for (uint32_t p = 3; p < sums.size(); p += 2)
        if (sums[p] == 1)
            for (uint64_t q = uint64_t(p) * p; q < sums.size(); q += 2 * p)
                sums[q] = p;

    vector<uint32_t> acc_counts(sums.size());
    acc_counts[1] = 0;
    for (uint32_t v = 2; v < sums.size(); ++v) {
        if (sums[v] == 1)
            sums[v] = v;
        else {
            const uint32_t f = sums[v], g = v / sums[v];
            sums[v] = sums[g] + (g % f == 0 ? 0 : f);
        }

        acc_counts[v] = acc_counts[v - 1u] + (sums[ sums[v] ] == sums[v] ? 1 : 0);
    }

    for (uint32_t a, b; cin >> a >> b && a > 0; )
        cout << (acc_counts[b] - acc_counts[a - 1]) << endl;

    return 0;
}
