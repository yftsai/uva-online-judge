// #algebra
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

int gcd(int a, int b)
{
    for (; a % b != 0; swap(a, b))
        a %= b;
    return b;
}

int main()
{
    array<int, 10> pow10s;
    pow10s[0] = 1;
    for (uint16_t i = 1; i < pow10s.size(); ++i)
        pow10s[i] = pow10s[i - 1u] * 10;

    string fraction;
    for (int32_t j, case_number = 1; cin >> j && j >= 0 && cin >> fraction; ++case_number) {
        const uint16_t k = fraction.size() - 2 - j;
        const int n = stoi(fraction.substr(2));
        const int num = n - ((j == 0) ? 0 : (n / pow10s[j]));
        const int den = pow10s[k + j] - ((j == 0) ? 0 : pow10s[k]);

        const int d = gcd(num, den);
        cout << "Case " << case_number << ": " << (num / d) << "/" << (den / d) << endl;
    }

    return 0;
}
