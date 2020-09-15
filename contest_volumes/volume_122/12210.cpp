// #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> bages(10000), sages(10000);
    for (uint16_t case_number = 1, b, s; cin >> b >> s && (b > 0 || s > 0); ++case_number) {
        uint16_t min_bage = 60;
        bages.resize(b);
        for (auto &a: bages) {
            cin >> a;
            min_bage = min(a, min_bage);
        }

        sages.resize(s);
        for (auto &s: sages)
            cin >> s;

        const uint16_t left_count = ((b <= s) ? 0 : (b - s));
        cout << "Case " << case_number << ": " << left_count;
        if (left_count == 0)
            cout << endl;
        else
            cout << " " << min_bage << endl;
    }

    return 0;
}
