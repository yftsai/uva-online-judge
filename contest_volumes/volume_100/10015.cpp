// #dynamic_programming
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t primes[3500], prime_count = 0;
    primes[prime_count++] = 2;
    for (uint16_t i = 3, j; prime_count < 3500; i += 2) {
        for (j = 0; j < prime_count && primes[j] <= uint16_t(sqrt(i)) && i % primes[j] != 0; j++)
            ;
        if (j == prime_count || i % primes[j] != 0)
            primes[prime_count++] = i;
    }

    uint16_t positions[3502];
    for (uint16_t n = 1; n <= 3501; ++n) {
        uint16_t p = 0;
        for (uint16_t m = 2, q; m <= n; ++m, swap(p, q)) {
            const uint16_t prime = primes[n - m];
            const uint16_t kill = (prime - 1) % m;
            q = (kill + p) % (m - 1);
            q = (q < kill) ? q : (q + 1);
        }
        positions[n] = p + 1;
    }

    for (int n; cin >> n && n > 0; )
        cout << positions[n] << endl;

    return 0;
}
