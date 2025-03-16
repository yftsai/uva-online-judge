// #easy
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<char> signs(1, '+');
    vector<int> values;
    string line;

    uint16_t t;
    uint32_t n;
    for (cin >> t; t > 0 && cin >> line >> n; t--) {
        char sign = '+';
        uint32_t neg = 0;
        for (char c: line) {
            if (c == 'x') {
                if (signs.back() != sign)
                    neg++;
            }
            else if ('+' == c || '-' == c)
                sign = c;
            else if ('(' == c) {
                signs.push_back(signs.back() == sign ? '+' : '-');
                sign = '+';
            }
            else
                signs.pop_back();
        }

        values.resize(n);
        for (auto &v : values)
            cin >> v;

        sort(values.begin(), values.end());
        int32_t value = 0;
        for (uint32_t i = 0; i < neg; i++)
            value -= values[i];
        for (uint32_t i = neg; i < values.size(); i++)
            value += values[i];
        cout << value << endl;
    }

    return 0;
}
