// #arithmetic
#include <iostream>
using namespace std;

int main()
{
    constexpr uint16_t max_n = 1u << 15;
    bool is_composite[max_n] = { false };
    uint16_t primes[3512], prime_count = 0;
    uint16_t counts[max_n / 2 + 1] = { 0 };

    primes[prime_count++] = 2;
    counts[(2 + 2)/2]++;
    for (uint16_t q = 3; q < max_n; q += 2)
        if (!is_composite[q]) {
            primes[prime_count++] = q;
            for (uint32_t i = uint32_t(q) * q; i < max_n; i += q)
                is_composite[i] = true;
            for (uint32_t i = 1; i < prime_count && primes[i] < max_n - q; i++)
                counts[(primes[i] + q) / 2]++;
        }

    for (int n; cin >> n && n >=4; )
        cout << counts[n / 2] << endl;
    return 0;
}
