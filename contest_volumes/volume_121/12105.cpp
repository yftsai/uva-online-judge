// #dynamic_programming
// The basic idea is to construct states around match counts and remaider of
// the modulo, but big integers impose significant overhead.
// The optimization of only storing the count of digits and its most significant
// digit was found from several sources online. The implementation here is in a
// top-down fashion.
#include <iostream>
#include <vector>
using namespace std;

const int match_counts[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const pair<int, int> not_found(-2, -1);
const pair<int, int> unknown(-1, -1);

// Given c matches and some significant digits which are specified by only
// their remainder r of modulo m,
// returns the maximal extension by its count of digits and its most
// significant digit.
// The extension combined with the implicit given digits is a multiple of m.
pair<int, int> &find_max(int c, int m, int r, vector<vector<pair<int, int>>> &table)
{
    if (table[c][r] == unknown) {
        for (int d = 0; d < 10; d++)
            if (c >= match_counts[d]) {
                int rem = (r * 10 + d) % m;
                if (rem == 0 && (table[c][r] == unknown || table[c][r] < pair<int, int>(1, d)))
                    table[c][r] = pair<int, int>(1, d);

                int mat = c - match_counts[d];
                pair<int, int> p = find_max(mat, m, rem, table);
                if (p != not_found) {
                    p = pair<int, int>(p.first + 1, d);
                    table[c][r] = max(p, (table[c][r] == unknown) ? p : table[c][r]);
                }
            }
        if (table[c][r] == unknown)
            table[c][r] = not_found;
    }
    return table[c][r];
}

int main()
{
    for (int case_count = 1, n, m; (cin >> n >> m) && n != 0; case_count++) {
        vector<vector<pair<int, int>>> table(n + 1, vector<pair<int, int>>(m + 1, unknown));
        pair<int, int> p = find_max(n, m, 0, table);

        if (p == not_found)
            cout << "Case " << case_count << ": -1" << endl;
        else {
            cout << "Case " << case_count << ": ";
            bool is_leading_zero = true;
            for (int length = p.first, c = n, r = 0; length > 0; length--) {
                int d = table[c][r].second;
                if (!is_leading_zero || d != 0 || length == 1) {
                    cout << d;
                    is_leading_zero = false;
                }
                c = c - match_counts[d];
                r = (r * 10 + d) % m;
            }
            cout << endl;
        }
    }

    return 0;
}
