// #string_search
#include <iostream>
#include <string>
using namespace std;

int main()
{
    uint16_t t;
    string s, r;

    for (cin >> t; cin >> s && t > 0; t--) {
        r.assign(s.rbegin(), s.rend());
        s.append(s.begin(), s.end());

        size_t pos = s.find(r, 1);
        if (0 < pos && pos < r.size())
            cout << "alindrome" << endl;
        else if (pos == r.size())
            cout << "palindrome" << endl;
        else
            cout << "simple" << endl;
    }

    return 0;
}
