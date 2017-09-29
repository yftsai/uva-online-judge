// #easy #exponentiating_by_squaring
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
    vector<uint32_t> primes(1, 2);
    auto is_prime = [&primes](uint32_t q) {
        for (uint32_t i = 0; i < primes.size() && primes[i] <= uint32_t(sqrt(q)); i++)
            if (q % primes[i] == 0)
                return false;
        return true;
    };

    for (uint32_t q = 3; q < uint32_t(sqrt(1000)) * 1000u; q += 2)
        if (is_prime(q))
            primes.push_back(q);

    for (uint32_t p, a; cin >> p >> a && p > 0; ) {
        if (is_prime(p))
            cout << "no" << endl;
        else {
            uint32_t aexps[32];
            aexps[0] = a;
            for (uint32_t i = 1, b = 2; i < 32 && b <= p; i++, b *= 2)
                aexps[i] = (uint64_t(aexps[i - 1]) * aexps[i - 1]) % p;

            uint32_t r = 1;
            for (uint32_t i = 0, exp = p; exp > 0; i++, exp /= 2)
                if (exp % 2 == 1)
                    r = (uint64_t(r) * aexps[i]) % p;
            cout << ((a == r) ? "yes" : "no") << endl;
        }
    }

    return 0;
}
