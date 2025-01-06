// #easy
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string first, second;

    uint16_t t;
    cin >> t;
    for (uint16_t cno = 1; cno <= t && cin >> first; cno++) {
        second = first.substr((first.size() + 1) / 2);
        first.resize(first.size() - second.size());
        reverse(second.begin(), second.end());

        uint32_t s = 0;
        while (first.size() > 0) {
            if (first.size() > second.size()) {
                s = (s << 1) | (first.back() - '0');
                first.pop_back();
            }
            else if ((first.back() == '0' && second.back() == '0') || second.back() == '1') {
                s = (s << 1) | (second.back() - '0');
                second.pop_back();
            }
            else {
                s = (s << 1) | 1u;
                first.back() = '0';
                second.pop_back();
            }
            s %= 1000000007u;
        }

        cout << "Case #" << cno << ": " << s << endl;
    }

    return 0;
}
