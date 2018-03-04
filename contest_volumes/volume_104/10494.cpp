// #trivial
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string num;
    uint32_t n;
    char op;
    while (cin >> num >> op >> n) {
        bool is_leading_zero = true;
        uint64_t r = 0;
        for (char d: num) {
            r = r * 10 + d - '0';
            uint32_t q = r / n;
            is_leading_zero = (is_leading_zero && q == 0);
            if (op == '/' && !is_leading_zero)
                cout << q;
            r %= n;
        }
        if (op == '/')
            cout << (is_leading_zero ? "0" : "") << endl;
        else
            cout << r << endl;
    }
    return 0;
}
