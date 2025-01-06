// #easy
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<string> names;
    for (uint16_t n; cin >> n && n > 0; ) {
        names.resize(n);
        for (auto &s: names)
            cin >> s;

        sort(names.begin(), names.end());

        auto &s = names[n / 2 - 1], &t = names[n / 2];
        uint16_t i = 0;
        for (; i < s.size() && i < t.size() && s[i] == t[i]; i++)
            ;

        if (i + 1u < s.size()) {
            i += (s[i] + 1 == t[i] && i + 1u == t.size()) ? 1 : 0;
            for (; i < s.size() && s[i] == 'Z'; i++)
                ;
            if (i + 1u < s.size()) {
                s[i]++;
                s.resize(i + 1);
            }
        }
        cout << s << endl;
    }

    return 0;
}
