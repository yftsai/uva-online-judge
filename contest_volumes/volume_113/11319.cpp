// According to the forum, there is an implicit assumption that a_n are integers.
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    for (cin >> n; n > 0; --n) {
        uint64_t fs[1500];
        for (auto &f: fs)
            cin >> f;

        uint16_t as[7];
        for (uint64_t i = 0, f = fs[1023]; i < 7; ++i, f >>= 10)
            as[i] = f % 1024u;

        bool is_valid = all_of(as, as + 7, [](uint16_t a) { return a < 1001; });
        for (uint16_t x = 1; x <= 1500 && is_valid; ++x) {
            uint64_t b = 1;
            for (uint16_t i = 0; i < 7; ++i, b = (numeric_limits<uint64_t>::max() / x >= b) ? b * x : 0)
                if (as[i] == 0 || (b > 0 && as[i] <= fs[x - 1] / b))
                    fs[x - 1] -= b * as[i];
                else
                    is_valid = false;
            is_valid = (is_valid && fs[x - 1] == 0);
        }

        if (is_valid) {
            cout << as[0];
            for (int i = 1; i < 7; ++i)
                cout << " " << as[i];
            cout << endl;
        }
        else
            cout << "This is a smart sequence!" << endl;
    }

    return 0;
}
