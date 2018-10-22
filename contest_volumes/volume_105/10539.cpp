// #prime_factorization #easy
#include <iostream>
#include <vector>
using namespace std;

uint32_t count(const vector<uint32_t> &primes, uint64_t n)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < primes.size() && uint64_t(primes[i]) * primes[i] <= n; i++)
        for (uint64_t v = uint64_t(primes[i]) * primes[i]; v <= n; v *= primes[i])
            count++;
    return count;
}

int main()
{
    vector<uint32_t> primes(1, 2);
    for (uint32_t i = 3, j; i < 1000 * 1000; i += 2) {
        for (j = 0; j < primes.size() && i / primes[j] >= primes[j] && i % primes[j] != 0; j++)
            ;
        if (j == primes.size() || i % primes[j] != 0)
            primes.push_back(i);
    }

    int n;
    uint64_t low, high;
    for (cin >> n; n > 0 && cin >> low >> high; n--)
        cout << (count(primes, high) - count(primes, low - 1)) << endl;

    return 0;
}
