// #cycle_detection
#include <iostream>
using namespace std;

int main()
{
    for (uint16_t num, den; cin >> num >> den; ){
        auto f = [den](uint16_t n) { return (n * 10) % den; };

        uint16_t n = (num % den);
        uint16_t m = f(n);
        while (n != m) {
            n = f(n);
            m = f(f(m));
        }

        uint16_t len = 0;
        do {
            n = f(n);
            m = f(f(m));
            ++len;
        } while (n != m);

        n = num % den;
        m = n;
        for (uint16_t i = 0; i < len; ++i)
            m = f(m);
        uint16_t start = 0;
        for (; n != m; n = f(n), m = f(m))
            ++start;

        cout << num << "/" << den << " = " << (num / den) << ".";
        n = num % den;
        for (uint16_t i = 0; i < min<uint16_t>(start + len, 50); ++i, n = f(n))
            cout << ((i == start) ? "(" : "") << ((n * 10) / den);
        cout << (((start + len) > 50) ? "...)" : ")") << endl;
        cout << "   " << len << " = number of digits in repeating cycle" << endl;
        cout << endl;
    }

    return 0;
}
