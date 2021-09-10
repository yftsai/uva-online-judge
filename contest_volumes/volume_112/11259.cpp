// #dynamic_programming
#include <iostream>
#include <array>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
    uint16_t n, q;
    array<uint16_t, 4> cs;
    array<uint32_t, 4> ds;
    uint32_t v;
    vector<int64_t> counts;

    for (cin >> n; n > 0; n--) {
        for (auto &c: cs)
            cin >> c;

        counts.assign(1000 * 100 + 1, 0);
        counts[0] = 1;
        for (const auto c: cs)
            for (uint32_t i = c; i < counts.size(); i++)
                counts[i] += counts[i - c];

        for (cin >> q; q > 0; q--) {
            for (auto &d: ds)
                cin >> d;
            cin >> v;

            int64_t count = 0;
            for (uint16_t s = 0; s < 16; s++) {
                const bitset<4> bs(s);

                int32_t value = v;
                for (uint16_t i = 0; i < cs.size(); i++)
                    if (bs.test(i))
                        value -= cs[i] * (ds[i] + 1);

                if (value >= 0)
                    count += (bs.count() % 2 == 0) ? counts[value] : -counts[value];
            }
            cout << count << endl;
        }
    }

    return 0;
}
