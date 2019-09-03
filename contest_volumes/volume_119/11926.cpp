// #easy
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    constexpr uint32_t max_count = 1000 * 1000;
    for (uint16_t n, m; cin >> n >> m && (n > 0 || m > 0); ) {
        bitset<max_count> time;
        bool has_conflict = false;

        for (uint32_t b, e; n > 0 && cin >> b >> e; --n)
            for (; b < e && !has_conflict; ++b) {
                has_conflict = time[b];
                time.set(b);
            }
        for (uint32_t b, e, r; m > 0 && cin >> b >> e >> r; --m)
            for (uint32_t c = b; c < max_count && !has_conflict; c += r)
                for (uint32_t d = c; d < c + e - b && d < max_count && !has_conflict; ++d) {
                    has_conflict = time[d];
                    time.set(d);
                }

        cout << (has_conflict ? "CONFLICT" : "NO CONFLICT") << endl;
    }

    return 0;
}
