// prime_factorization
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

uint16_t count_divisor(const vector<uint16_t> &prime_factors, uint32_t n)
{
    uint16_t count = 1;
    while (prime_factors[n] != 0) {
        const uint16_t p = prime_factors[n];
        uint16_t exp = 0;
        for (; n % p == 0; n /= p)
            ++exp;
        count *= exp + 1;
    }
    if (n != 1)
        count *= 2;
    return count;
}

vector<uint32_t> init()
{
    vector<uint16_t> prime_factors(1000 * 1000 + 1, 0);

    for (uint32_t n = 4; n < prime_factors.size(); n += 2)
        prime_factors[n] = 2;
    for (uint16_t n = 3; n < 1000; n += 2)
        if (prime_factors[n] == 0)
            for (uint32_t m = uint32_t(n) * n; m < prime_factors.size(); m += n)
                prime_factors[m] = n;

    vector<uint32_t> ms;
    ms.push_back(1);
    ms.push_back(2);
    uint16_t max_divisor_count = 2;
    for (uint32_t n = 3; n <= 1000u * 1000; ++n) {
        uint16_t divisor_count = count_divisor(prime_factors, n);
        if (divisor_count >= max_divisor_count) {
            max_divisor_count = divisor_count;
            ms.push_back(n);
        }
    }

    return ms;
}

int main()
{
    const vector<uint32_t> ms = init();

    uint32_t t, n;
    for (cin >> t; t > 0 && cin >> n; --t)
        cout << *prev(upper_bound(ms.begin(), ms.end(), n)) << endl;

    return 0;
}
