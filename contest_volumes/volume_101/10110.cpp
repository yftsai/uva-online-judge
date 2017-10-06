// #arithmetic #easy
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
    vector<uint16_t> primes(1, 2);
    constexpr uint32_t prime_limit = 1u << 16;
    bitset<prime_limit> is_prime;
    for (uint32_t q = 3; q < prime_limit; q += 2)
        if (!is_prime.test(q)) {
            primes.push_back(q);
            for (uint32_t m = q * q; m < prime_limit; m += q)
                is_prime.set(m);
        }

    for (uint32_t n; cin >> n && n > 0; ) {
        bool is_on = true;
        for (size_t i = 0; i < primes.size() && primes[i] * primes[i] <= n && is_on; i++)
            for (; n % primes[i] == 0; n /= primes[i])
                is_on = !is_on;
        if (n > 1)
            is_on = false;
        cout << (is_on ? "yes" : "no") << endl;
    }
    return 0;
}
