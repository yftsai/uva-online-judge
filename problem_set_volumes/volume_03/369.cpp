// #combinatorics
#include <iostream>
#include <vector>
using namespace std;

uint32_t gcd(uint32_t a, uint32_t b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

int main()
{
    for (uint16_t n, m; cin >> n >> m && (n != 0 || m != 0); ) {
        vector<uint32_t> factors(1, 1);
        for (uint32_t i = 1; i <= m; i++) {
            uint32_t f = n + 1 - i;
            if (factors.back() <= UINT32_MAX / f)
                factors.back() *= f;
            else
                factors.push_back(f);

            f = i;
            for (size_t i = 0; i < factors.size() && f > 1; i++) {
                uint32_t g = gcd(factors[i], f);
                factors[i] /= g;
                f /= g;
            }
        }
        for (; factors.size() > 1; factors.pop_back())
            factors[factors.size() - 2] *= factors.back();
        cout << n << " things taken " << m << " at a time is " << factors[0] << " exactly." << endl;
    }
    return 0;
}
