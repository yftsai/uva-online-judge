// #arithmetic
// The performance of Sieve of Eratosthenes is critical.
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
    constexpr uint32_t prime_value_limit = 30 * 1000 * 1000;
    bitset<prime_value_limit> is_primes;
    is_primes.set();

    for (uint32_t q = 3; q < prime_value_limit; q += 2)
        if (is_primes.test(q))
            for (uint64_t r = uint64_t(q) * q; r < prime_value_limit; r += 2 * q)
                is_primes.reset(r);

    vector<uint32_t> primes(1, 2);
    for (uint32_t p = 3; p < prime_value_limit; p += 2)
        if (is_primes.test(p))
            primes.push_back(p);

    for (uint64_t n; cin >> n; ) {
        if (n == 0)
            cout << 0 << endl;
        else {
            while (n % 2 == 0)
                n /= 2;
            uint32_t count = 1;
            for (uint32_t i = 0; i < primes.size() && n > 1; i++)
                if (n % primes[i] == 0) {
                    uint32_t exp = 0;
                    for (; n % primes[i] == 0; exp++)
                        n /= primes[i];
                    count *= (exp + 1);
                }
            if (n > 1)
                count *= 2;
            cout << count << endl;
        }
    }

    return 0;
}
