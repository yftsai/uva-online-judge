// #prime_factorization
/*
    interesting primes:
    ... 215393 215399 215417 215443                         p^3 < 10**16
    215447 215459 215461 ...                                p^3 > 10**16
    ... 99999959 99999971 99999989                          p < 10**8
    100000007 100000037 100000039                           p > 10**8
    ... 9999999999999937 9999999999999917 9999999999999887  p < 10**16
*/
#include <iostream>
#include <bitset>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <cmath>
using namespace std;

// The values of a, b, d are up to 54 bits
uint64_t mulrem(uint64_t a, uint64_t b, uint64_t d)
{
    const uint64_t as[2] = { a & 0x0FFFFFFF, a >> 28};
    const uint64_t bs[2] = { b & 0x0FFFFFFF, b >> 28};
    uint64_t rs[4] = { as[0] * bs[0], as[0] * bs[1], as[1] * bs[0], as[1] * bs[1] };
    for (auto i = 0; i < 4; i++) {
        rs[1] = (rs[1] << 7) % d;
        rs[2] = (rs[2] << 7) % d;
    }
    for (auto i = 0; i < 7; i++)
        rs[3] = (rs[3] << 8) % d;
    return accumulate(begin(rs), end(rs), uint64_t(0)) % d;
}

default_random_engine engine((random_device())());

bool test_prime(uint64_t n)
{
    bool is_prime = true;
    for (auto i = 0; i < 8 && is_prime; i++) {
        const uint64_t a = uniform_int_distribution<uint64_t>(2, n - 1)(engine);
        uint64_t b = a, e = (n - 1) / 2, r = 1;
        for (; e > 0; e /= 2, b = mulrem(b, b, n))
            if (e % 2 == 1)
                r = mulrem(r, b, n);
        is_prime = (r == 1 || r == (n - 1));
    }
    return is_prime;
}

uint64_t gcd(uint64_t a, uint64_t b)
{
    for (; a % b != 0; swap(a, b))
        a %= b;
    return b;
}

uint64_t rho(uint16_t iteration_limit, uint64_t n)
{
    const uint64_t c = uniform_int_distribution<uint64_t>(1, n - 1)(engine);
    auto f = [n, c](uint64_t x) { return (mulrem(x, x, n) + c) % n; };

    uint64_t a, b, g = 1;
    a = uniform_int_distribution<uint64_t>(2, n - 1)(engine);
    b = f(a);
    for (uint16_t x = 0; x < iteration_limit && g == 1; x++, a = f(a), b = f(f(b)))
        g = gcd((a >= b) ? (a - b) : (b -a), n);
    return g;
}

int main()
{
    vector<uint16_t> tiny_primes(1, 2);
    const uint32_t tiny_prime_limit = (1u << 8);
    {
        bitset<tiny_prime_limit / 2u - 1u> is_primes;
        is_primes.set();
        for (uint16_t i = 0; i < is_primes.size(); i++)
            if (is_primes[i]) {
                uint16_t p = 3u + 2u * i;
                tiny_primes.push_back(p);
                for (uint32_t j = (uint32_t(p) * p - 3u) / 2u; j < is_primes.size(); j += p)
                    is_primes.reset(j);
            }
    }

    uint16_t t;
    cin >> t;
    vector<uint64_t> factors, prime_factors;
    for (uint64_t n; t > 0 && cin >> n; t--, prime_factors.clear()) {
        cout << n << " = ";

        for (auto p: tiny_primes)
            if (n % p == 0)
                for (; n % p == 0; n /= p)
                    prime_factors.push_back(p);

        if (n > 1)
            factors.assign(1, n);
        while (factors.size() > 0) {
            uint64_t n = factors.back();
            factors.pop_back();

            if (n < tiny_prime_limit * tiny_prime_limit || test_prime(n))
                prime_factors.push_back(n);
            else {
                const uint16_t iteration_limit = sqrt(sqrt(n)) * 4;
                uint64_t f = 1;
                while (f == 1 || f >= n)
                    f = rho(iteration_limit, n);
                factors.push_back(n / f);
                factors.push_back(f);
            }
        }

        sort(prime_factors.begin(), prime_factors.end());
        bool is_first = true;
        for (auto b = prime_factors.begin(), e = prime_factors.begin(); b != prime_factors.end(); b = e) {
            uint16_t exp = 0;
            for (e = b; e != prime_factors.end() && *e == *b; e++)
                exp++;
            cout << (is_first ? "" : " * ") << *b;
            is_first = false;
            if (exp > 1)
                cout << "^" << exp;
        }

        cout << endl;
    }

    return 0;
}
