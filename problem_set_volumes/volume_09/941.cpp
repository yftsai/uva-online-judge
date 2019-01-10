// #permutation
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    uint64_t bases[20];
    bases[0] = 1;
    for (uint8_t i = 1; i < 20; ++i)
        bases[i] = bases[i - 1] * i;

    int sample_count;
    for (cin >> sample_count; sample_count > 0; --sample_count) {
        string s;
        uint64_t n;
        cin >> s >> n;

        sort(s.begin(), s.end());
        const uint8_t len = s.size();
        for (uint8_t i = 0; i + 1u < s.size(); ++i) {
            uint8_t j = n / bases[len - 1 - i];
            char c = s[i + j];
            copy_backward(s.begin() + i, s.begin() + i +j, s.begin() + i + j + 1);
            s[i] = c;
            n -= bases[len - 1 - i] * j;
        }
        cout << s << endl;
    }

    return 0;
}
