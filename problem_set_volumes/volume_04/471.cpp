// #easy
#include <iostream>
using namespace std;

bool is_digit_repeated(uint64_t n)
{
    bool digits[10];
    for (auto &d: digits)
        d = false;
    for (; n > 0; n /= 10)
        if (digits[n % 10])
            return true;
        else
            digits[n % 10] = true;
    return false;
}

int main()
{
    int case_count;
    for (cin >> case_count; case_count > 0; case_count--) {
        uint64_t s1, s2, n;
        cin >> n;
        for (s1 = n, s2 = 1; s1 <= 9876543210; s1 += n, s2 += 1)
            if (!is_digit_repeated(s1) && !is_digit_repeated(s2))
                cout << s1 << " / " << s2 << " = " << n << endl;
        if (case_count > 1)
            cout << endl;
    }
    return 0;
}
