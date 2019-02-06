// #prime_factorization
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
    const uint32_t max_n = 2 * 1000 * 1000;
    vector<uint32_t> phi(max_n + 1);
    vector<uint32_t> depth_accumulations(phi.size());

    vector<uint16_t> factors(phi.size(), 1);
    depth_accumulations[1] = 0;
    for (uint32_t n = 2; n < phi.size(); ++n) {
        if (factors[n] == 1 && n < uint16_t(sqrt(max_n)))
            for (uint32_t m = n * n; m < phi.size(); m += n)
                factors[m] = n;

        if (factors[n] == 1)
            phi[n] = n - 1;
        else {
            const uint16_t p = factors[n];
            const uint32_t r = n / p;
            phi[n] = phi[r] * p - ((r % p != 0) ? phi[r] : 0);
        }
        const uint32_t depth = depth_accumulations[ phi[n] ] - depth_accumulations[ phi[n] - 1];
        depth_accumulations[n] = depth_accumulations[n - 1] + depth + 1;
    }

    uint32_t set_count, m, n;
    for (cin >> set_count; set_count > 0 && cin >> m >> n; --set_count)
        cout << (depth_accumulations[n] - depth_accumulations[m - 1]) << endl;

    return 0;
}
