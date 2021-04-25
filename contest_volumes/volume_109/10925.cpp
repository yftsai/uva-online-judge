// #easy #big_integer
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <cinttypes>
using namespace std;

class bigint
{
    public:
        static constexpr uint16_t strsize = 24;

        bigint(uint32_t value):
            values({ value % base, value / base, 0 })   {}

        bigint &operator+=(const string &);
        bigint &operator/=(const uint16_t);

        friend ostream &operator<<(ostream &, const bigint &);

    private:
        constexpr static uint32_t base = 1000 * 1000 * 100;
        constexpr static int16_t exp = 8;
        array<uint32_t, 3> values;
};

bigint &bigint::operator+=(const string &addend)
{
    size_t pos = addend.size();
    uint32_t carry = 0;
    for (auto vit = values.begin(); vit != values.end(); ++vit, pos -= exp) {
        *vit += carry + stoi(addend.substr(pos - exp, exp));
        carry = *vit / base;
        *vit %= base;
    }

    return *this;
}

bigint &bigint::operator/=(const uint16_t divider)
{
    uint32_t carry = 0;
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
        *it += carry * base;
        carry = *it % divider;
        *it /= divider;
    }

    return *this;
}

ostream &operator<<(ostream &os, const bigint &bi)
{
    char s[bigint::strsize + 1];
    for (uint16_t i = 0; i < bi.values.size(); i++)
        sprintf(s + 8 * i, "%08" PRIu32, bi.values[bi.values.size() - 1 - i]);

    size_t size = bigint::strsize;
    reverse(s, s + size);
    for (; size > 1 && s[size - 1] == '0'; size--)
        s[size -  1] = '\0';
    reverse(s, s + size);
    os << s;

    return os;
}

int main()
{
    string v;
    uint32_t b = 1;
    for (uint16_t n, f; cin >> n >> f && n > 0; b++) {
        bigint sum = 0;
        for (uint16_t i = 0; i < n && cin >> v; i++) {
            reverse(v.begin(), v.end());
            v.resize(bigint::strsize, '0');
            reverse(v.begin(), v.end());
            sum += v;
        }

        cout << "Bill #" << b << " costs " << sum;
        sum /= f;
        cout << ": each friend should pay " << sum << endl;
        cout << endl;
    }

    return 0;
}
