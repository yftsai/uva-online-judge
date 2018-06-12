// #longest_common_subsequence
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string s, t;
    for (string s, t; getline(cin, s) && getline(cin, t); ) {
        vector<int> rows[2];
        rows[0].resize(s.size() + 1, 0);
        rows[1].resize(s.size() + 1, 0);

        for (size_t i = 0; i < t.size(); i++, rows[0].swap(rows[1]))
            for (size_t j = 0; j < s.size(); j++)
                if (t[i] == s[j])
                    rows[1][j + 1] = rows[0][j] + 1;
                else
                    rows[1][j + 1] = max(rows[0][j + 1], rows[1][j]);
        cout << rows[0].back()  << endl;
    }
    return 0;
}
