#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(const string &s, const string &t)
{
    for (auto p = s.begin(), q = t.begin(); p != t.end(); ++p, ++q) {
        p = (p == s.end()) ? t.begin() : p;
        q = (q == t.end()) ? s.begin() : q;
        if (*p > *q)
            return true;
        else if (*p < *q)
            return false;
    }
    return false;
}

int main()
{
    vector<string> pints;
    for (uint16_t n; cin >> n && n > 0; ) {
        pints.resize(n);
        for (auto &i: pints)
            cin >> i;

        sort(pints.begin(), pints.end(), compare);
        for (const auto &i: pints)
            cout << i;
        cout << endl;
    }

    return 0;
}
