// #trivial
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct number
{
    int value;
    int16_t remainder;
    bool is_odd;

    bool operator<(const number &n) const
    {
        if (remainder != n.remainder)
            return remainder < n.remainder;
        else if (is_odd != n.is_odd)
            return is_odd;
        else if (is_odd)
            return value > n.value;
        else
            return value < n.value;
    }
};

int main()
{
    vector<number> numbers(10000);
    for (uint16_t n, m; cin >> n >> m && cout << n << " " << m << endl && n > 0; ) {
        numbers.resize(n);
        for (auto &num: numbers) {
            cin >> num.value;
            num.remainder = num.value % m;
            num.is_odd = (num.value % 2 != 0);
        }

        sort(numbers.begin(), numbers.end());
        for (const auto &num: numbers)
            cout << num.value << endl;
    }

    return 0;
}
