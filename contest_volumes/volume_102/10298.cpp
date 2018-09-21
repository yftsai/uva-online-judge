// #prime_factorization
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool is_splittable(const string &s, unsigned int n)
{
    size_t len = s.size() / n;
    for (size_t i = 0; i < len; i++)
        for (size_t j = i + len; j < s.size(); j += len)
            if (s[j] != s[i])
                return false;
    return true;
}

int main()
{
    vector<unsigned int> primes(1, 2);
    for (unsigned int n = 3; n < 1000; n+=2) {
        bool is_prime = true;
        for (size_t i = 0; i < primes.size() && is_prime && n / primes[i] >= primes[i]; i++)
            is_prime = (n % primes[i] != 0);
        if (is_prime)
            primes.push_back(n);
    }

    for (string s; cin >> s && s[0] != '.'; ) {
        unsigned int n = 1;
        for (size_t i = 0; i < primes.size() && s.size() >= primes[i]; i++)
            while (s.size() % primes[i] == 0 && is_splittable(s, primes[i])) {
                s.resize(s.size() / primes[i]);
                n *= primes[i];
            }
        if (is_splittable(s, s.size()))
            n *= s.size();
        cout << n << endl;
    }

    return 0;
}
