// #string_search
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

static void extend(const string &s, vector<uint32_t> &lengths)
{
    auto idx = lengths.size();
    if (idx == 0)
        lengths.push_back(0);
    else {
        auto len = lengths[idx - 1];
        while (s[len] != s[idx] && len > 0)
            len = lengths[len - 1];
        lengths.push_back((s[len] == s[idx]) ? len + 1 : 0);
    }
}

int main()
{
    uint16_t t;
    string s;
    vector<uint32_t> lengths;   // Each position stores the length of the
                                // shorter secret word to continue extending.

    for (cin >> t; t > 0 && cin >> s; t--) {
        lengths.resize(0);

        uint32_t max_length = 0, length = 0;
        for (uint32_t i = s.size(); i > 0; i--) {
            const auto idx = i - 1;

            // find the prefix of s that can be extended
            while (s[length] != s[idx] && length > 0)
                length = lengths[length - 1];

            if (s[length] == s[idx]) {
                length++;
                if (length > max_length) {
                    max_length = length;
                    extend(s, lengths);
                }
            }
        }

        s.resize(max_length);
        reverse(s.begin(), s.end());
        cout << s << endl;
    }

    return 0;
}
