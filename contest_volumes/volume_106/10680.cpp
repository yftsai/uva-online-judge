// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int get_exp(int n, int p)
{
    int exp = 0;
    for (; n >= p; n /= p, exp++)
        ;
    return exp;
}

int main()
{
    vector<int> primes(1, 2);
    for (int n = 3; n < 1000 * 1000; n += 2) {
        bool is_prime = true;
        for (size_t i = 0; i < primes.size() && is_prime && n / primes[i] >= primes[i]; i++)
            is_prime = (n % primes[i] != 0);
        if (is_prime)
            primes.push_back(n);
    }

    for (int n; (cin >> n) && n != 0; ) {
        int lcm = 1;
        int exp2 = get_exp(n, 2), exp5 = get_exp(n, 5);
        for (int i = min(exp2, exp5); i < max(exp2, exp5); i++, lcm %= 10)
            lcm *= (exp2 > exp5) ? 2 : 5;

        for (size_t i = 0; i < primes.size() && primes[i] <= n; i++)
            if (primes[i] != 2 && primes[i] != 5)
                for (int j = 0; j < get_exp(n, primes[i]); j++, lcm %= 10)
                    lcm *= primes[i];
        cout << lcm << endl;
    }

    return 0;
}
