// #easy
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    uint16_t test_count, degree;
    vector<uint16_t> cs;
    for (cin >> test_count; test_count > 0 && cin >> degree; --test_count) {
        cs.resize(degree + 1);
        for (auto &c: cs)
            cin >> c;
        uint32_t d, k;
        cin >> d >> k;

        uint32_t m = sqrt(k * 2 / d);
        while (k > m * (m + 1) / 2 * d)
            ++m;
        uint64_t a = cs.front(), b = m;
        for (uint32_t i = 1; i < cs.size(); ++i, b *= m)
            a += cs[i] * b;
        cout << a << endl;
    }

    return 0;
}
