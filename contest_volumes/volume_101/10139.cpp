// #prime_factorization
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> primes(1u, 2);
    {
        vector<bool> is_prime(1u << 16, true);
        for (uint32_t p = 3; p < is_prime.size(); p += 2u)
            if (is_prime[p]) {
                primes.push_back(p);
                for (uint32_t q = p * p; q < is_prime.size(); q += p)
                    is_prime[q] = false;
            }
    }

    for (uint32_t n, m; cin >> n >> m; ) {
        bool is_dividable = m > 0;

        if (m == 0)
            is_dividable = false;
        else if (n == 0)
            is_dividable = (m == 1);
        else {
            uint32_t r = m;
            for (auto p: primes)
                if (!is_dividable || uint32_t(p) * p > r)
                    break;
                else if (r % p == 0) {
                    uint16_t mp_count = 0;
                    for (; r % p == 0; r /= p)
                        ++mp_count;
                    uint16_t np_count = 0;
                    for (uint32_t s = n; s >= p; s /= p)
                        np_count += s / p;
                    is_dividable = (mp_count <= np_count);
                }
            is_dividable = is_dividable && ((r == 1u) || (r <= n));
        }

        if (is_dividable)
            cout << m << " divides " << n << "!" << endl;
        else
            cout << m << " does not divide " << n << "!" << endl;
    }
    return 0;
}
