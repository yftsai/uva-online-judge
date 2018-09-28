// #string_searching
#include <iostream>
#include <string>
using namespace std;

int main()
{
    const uint32_t max_length = 100 * 1000;
    uint32_t indexes[max_length];
    indexes[0] = max_length;

    for (string s, r; cin >> s; ) {
        r.assign(s.rbegin(), s.rend());
        for (uint32_t i = 1, j; i < r.size(); i++) {
            for (j = indexes[i - 1]; j != max_length && r[j + 1] != r[i]; j = indexes[j])
                ;
            if (j == max_length)
                indexes[i] = (r[0] == r[i]) ? 0 : max_length;
            else
                indexes[i] = j + 1;
        }

        uint32_t mlen = 0;      // matched length
        for (uint32_t i = 0; i < s.size(); i++) {
            while (mlen > 0 && r[mlen] != s[i])
                mlen = (indexes[mlen - 1] == max_length) ? 0 : (indexes[mlen - 1] + 1);
            if (r[mlen] == s[i])
                mlen++;
        }
        cout << s << r.substr(mlen) << endl;
    }

    return 0;
}
