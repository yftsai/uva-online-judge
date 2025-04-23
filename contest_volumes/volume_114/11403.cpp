// #easy
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string a, b, c;
    string spaces, dashes;

    bool is_first_case = true;
    for (string a, b; cin >> a >> b && !(a == "0" && b == "0"); ) {
        if (is_first_case)
            is_first_case = false;
        else
            cout << endl;

        uint32_t va = 0, vb = 0;
        for (char c: a)
            va = 2 * va + c - '0';
        for (char c: b)
            vb = 2 * vb + c - '0';

        uint64_t vc = uint64_t(va) * vb;
        c.clear();
        do {
            c.append(1, char('0' + vc % 2));
            vc /= 2;
        } while (vc > 0);
        reverse(c.begin(), c.end());

        uint16_t width = max(a.size() + b.size() - 1, c.size());
        spaces.resize(width - a.size(), ' ');
        cout << spaces << a << endl;
        spaces.resize(width - b.size(), ' ');
        cout << spaces << b << endl;
        dashes.resize(max(a.size(), b.size()), '-');
        spaces.resize(width - dashes.size(), ' ');
        cout << spaces << dashes << endl;

        spaces.resize(width - a.size() + 1, ' ');
        for (auto it = b.rbegin(); it != b.rend(); it++) {
            spaces.resize(spaces.size() - 1);
            cout << spaces;
            for (char c: a)
                cout << ((c - '0' == 1 && *it - '0' == 1) ? '1' : '0');
            cout << endl;
        }
        dashes.resize(width, '-');
        cout << dashes << endl;
        spaces.resize(width - c.size(), ' ');
        cout << spaces << c << endl;
    }

    return 0;
}
