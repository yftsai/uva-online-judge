// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void get_primes(uint16_t max_n, vector<uint16_t> *primes)
{
    primes->assign(1, 1);   // 1 is the special prime number in this problem
    primes->push_back(2);

    vector<bool> is_composite(max_n + 1u, false);
    for (uint16_t p = 3; p <= max_n; p += 2)
        if (!is_composite[p]) {
            primes->push_back(p);
            for (uint32_t q = uint32_t(p) * p; q <= max_n; q += 2 * p)
                is_composite[q] = true;
        }
}

int main()
{
    constexpr uint16_t max_n = 1000;
    vector<uint16_t> primes;
    get_primes(max_n, &primes);

    for (uint16_t n, c; cin >> n >> c; ) {
        uint16_t length = upper_bound(primes.begin(), primes.end(), n) - primes.begin();
        const uint16_t d = min<uint16_t>(c, (length + 1) / 2);
        const uint16_t begin = (length + 1) / 2 - d;
        const uint16_t end = length - begin;

        cout << n << " " << c << ":";
        for (uint16_t i = begin; i < end; ++i)
            cout << " " << primes[i];
        cout << endl;
        cout << endl;
    }

    return 0;
}
