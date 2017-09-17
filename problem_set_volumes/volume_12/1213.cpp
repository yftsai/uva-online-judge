// #easy #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    constexpr uint16_t max_n = 1120;
    constexpr uint16_t max_k = 14;

    vector<uint16_t> primes(1, 2);
    for (uint16_t q = 3; q <= max_n; q += 2) {
        bool is_prime = true;
        for (uint16_t p: primes)
            if (p * p > q || !(is_prime = q % p > 0))
                break;
        if (is_prime)
            primes.push_back(q);
    }

    vector<uint32_t> counts[max_k];
    for (uint16_t p = 0; p < primes.size(); p++) {
        for (uint16_t set_size = min<uint16_t>(p + 1, max_k); set_size > 1; set_size--) {
            if (counts[set_size - 2].size() + primes[p] > counts[set_size - 1].size())
                counts[set_size - 1].resize(min<size_t>(max_n, counts[set_size - 2].size() + primes[p]), 0);
            for (uint16_t set_sum = 1; set_sum <= counts[set_size - 2].size(); set_sum++)
                if (set_sum + primes[p] <= counts[set_size - 1].size())
                    counts[set_size - 1][set_sum + primes[p] -1] += counts[set_size - 2][set_sum - 1];
        }
        counts[0].resize(primes[p], 0);
        counts[0][ primes[p] - 1] = 1;
    }

    for (uint16_t n, k; cin >> n >> k && n > 0; )
        cout << counts[k - 1][n - 1] << endl;

    return 0;
}
