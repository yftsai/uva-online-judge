// #easy
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void get_primes(vector<int> *primes)
{
    const int sqrt = 1 << 8;
    vector<bool> is_composite(sqrt * sqrt, false);
    for (int p = 3; p < sqrt * sqrt; p += 2)
        if (!is_composite[p]) {
            primes->push_back(p);
            for (int q = p * p; p < sqrt && q < sqrt * sqrt; q += p)
                is_composite[q] = true;
        }
}

int main()
{
    vector<int> primes(1, 2);
    get_primes(&primes);

    for (int g; cin >> g && g != 0; ) {
        cout << g << " =";
        bool is_first = true;
        if (g < 0) {
            cout << " -1";
            is_first = false;
            g = -g;
        }
        for (uint16_t i = 0; i < primes.size() && primes[i] <= int(sqrt(g)); i++)
            for (; g % primes[i] == 0; g /= primes[i], is_first = false)
                cout << (is_first ? " " : " x ") << primes[i];
        if (g > 1)
            cout << (is_first ? " " : " x ") << g;
        cout << endl;
    }

    return 0;
}
