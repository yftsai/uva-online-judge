// #dynamic_programming
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    string s, t;
    int lengths[301][301];
    for (bool is_first = true; cin >> s >> t; is_first = false) {
        for (uint16_t i = 0; i < t.size(); i++)
            lengths[s.size()][i] = 0;
        for (uint16_t i = 0; i <= s.size(); i++)
            lengths[i][t.size()] = 0;

        int max_length = 0;
        for (uint16_t i = s.size(); i > 0; i--)
            for (uint16_t j = t.size(); j > 0; j--)
                max_length = max(max_length, lengths[i - 1][j - 1] = (s[i - 1] == t[j - 1]) ? (lengths[i][j] + 1) : 0);

        set<string> lcs_set;
        if (max_length > 0)
            for (uint16_t i = 0; i < s.size(); i++)
                if (find(lengths[i], lengths[i] + t.size(), max_length) != lengths[i] + t.size())
                    lcs_set.insert(s.substr(i, max_length));

        if (!is_first)
            cout << endl;
        if (max_length == 0)
            cout << "No common sequence." << endl;
        else
            for (const string &s: lcs_set)
                cout << s << endl;
    }
    return 0;
}
