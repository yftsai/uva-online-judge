// #easy
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string p, m;
    for (uint16_t b; cin >> b && b > 1; ) {
        cin >> p >> m;

        const uint32_t mv = stoi(m, 0, b);
        uint64_t pv = 0;
        for (char c: p)
            pv = (pv * b + c - '0') % mv;

        uint32_t msd = 1;
        while (uint64_t(msd) * b <= pv)
            msd *= b;
        for (; msd > 0; msd /= b) {
            cout << (pv / msd);
            pv %= msd;
        }
        cout << endl;
    }

    return 0;
}
