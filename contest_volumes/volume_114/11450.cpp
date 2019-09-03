// #easy #dynamic_programming
#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;

int main()
{
    constexpr uint16_t max_m = 200;
    uint32_t n;
    bitset<max_m + 1> is_used[2];
    for (cin >> n; n > 0; --n) {
        uint16_t m, c, k;
        cin >> m >> c;
        is_used[0].reset();
        is_used[0].set(0);
        for (uint16_t i = 0; i < c && cin >> k; ++i) {
            is_used[1].reset();
            for (uint16_t j = 0, p; j < k && cin >> p; ++j) {
                for (uint16_t total = 0; total + p <= m; ++total)
                    if (is_used[0][total])
                        is_used[1].set(total + p);
            }
            swap(is_used[0], is_used[1]);
        }
        uint16_t money;
        for (money = m; money > 0 && !is_used[0][money]; --money)
            ;
        if (money == 0)
            cout << "no solution" << endl;
        else
            cout << money << endl;
    }

    return 0;
}
