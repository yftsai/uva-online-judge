// #greedy
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t t, k;
    string s, u;

    for (cin >> t; t > 0 && cin >> k >> s; t--) {
        uint16_t length = 0;
        u.clear();
        typedef pair<string::iterator, string::iterator> state;
        state current(s.begin(), s.begin());
        for (uint16_t i = 0; i < s.size(); i += k) {
            state next(s.begin() + i, s.begin() + i + k);
            sort(next.first, next.second);
            next.second = unique(next.first, next.second);
            const uint16_t ch_count = next.second - next.first;

            u.clear();
            set_intersection(
                current.first, current.second,
                next.first, next.second,
                back_inserter(u));

            if (u.size() == 0)
                length += ch_count;
            else if (u.size() == 1 && ch_count == 1)
                ;
            else if (u.size() == 1) {
                next.second = remove(next.first, next.second, u[0]);
                length += ch_count - 1;
            }
            else
                length += ch_count - 1;

            current = next;
        }
        cout << length << endl;
    }

    return 0;
}
