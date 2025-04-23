// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint32_t> primes;
    primes.reserve(100000);
    primes.push_back(2);
    for (uint32_t n = 3, i = 1, sq = 4; primes.size() < 100000; n += 2) {
        if (n > sq) {
            i++;
            sq = primes[i - 1] * primes[i - 1];
        }

        if (none_of(primes.begin(), primes.begin() + i, [&n](uint32_t p) { return n % p == 0; }))
            primes.push_back(n);
    }

    for (uint32_t n; cin >> n && n > 0; ) {
        auto it = lower_bound(primes.begin(), primes.end(), n);
        if (*it == n)
            cout << 0 << endl;
        else {
            n = *it;
            cout << (n - *(--it)) << endl;
        }
    }

    return 0;
}
