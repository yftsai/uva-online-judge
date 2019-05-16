// #cycle_detection
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    uint16_t test_count, m;
    pair<uint16_t, uint16_t> ab;
    uint32_t n;
    for (cin >> test_count; test_count > 0 && cin >> ab.first >> ab.second >> n >> m; --test_count) {
        const uint16_t d = uint16_t(pow(10, m));
        auto advance = [d](pair<uint16_t, uint16_t> *p) {
            p->first = (p->first + p->second) % d;
            swap(p->first, p->second);
            return p;
        };

        uint32_t i = 0;
        ab.first %= d;
        ab.second %= d;

        pair<uint16_t, uint16_t> cd = ab;
        for (advance(&cd); i < n && ab != cd; ++i, advance(advance(&cd)))
            advance(&ab);

        if (i < n) {
            size_t len;
            for (len = 1, advance(&ab), ++i; i < n && ab != cd; ++len, advance(&ab), ++i)
                ;

            for (uint16_t j = (n - i) % len; j > 0; --j)
                advance(&ab);
        }

        cout << ab.first << endl;
    }

    return 0;
}
