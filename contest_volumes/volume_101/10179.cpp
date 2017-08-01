// #factorization
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    vector<int> primes(1, 2);
    for (int i = 3; i <= int(sqrt(1000000000)) + 1; i += 2) {
        bool is_prime = true;
        for (size_t j = 0; j < primes.size() && primes[j] <= int(sqrt(i)) && is_prime; j++)
            is_prime = i % primes[j] != 0;
        if (is_prime)
            primes.push_back(i);
    }

    for (int n; cin >> n && n != 0; ) {
        vector<int> factors;
        int m = n;
        for (size_t i = 0; i < primes.size() && primes[i] <= int(sqrt(m)); i++)
            if (m % primes[i] == 0)
                for (factors.push_back(primes[i]); m % primes[i] == 0; m /= primes[i])
                    ;
        if (m > 1)
            factors.push_back(m);

        m = n;
        for (int i = 1; i < 1 << factors.size(); i++) {
            int sieve = 1, sign = 1;
            for (size_t j = 0; j < factors.size(); j++)
               if ((i & (1 << j)) != 0)
                  sieve *= factors[j], sign = -sign;
            m += (n-1) /sieve *sign;
        }
        cout << (m - ((n == 1) ? 0 : 1)) << endl;
    }
    return 0;
}
