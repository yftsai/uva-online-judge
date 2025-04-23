// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    typedef pair<uint16_t, uint16_t> soldier_t;
    vector<soldier_t> soldiers;

    for (uint16_t n, cn = 1; cin >> n && n > 0; cn++) {
        soldiers.resize(n);
        for (auto &s: soldiers)
            cin >> s.first >> s.second;

        sort(soldiers.begin(), soldiers.end(),
            [&soldiers](const soldier_t &s, const soldier_t &t) {
                return max(s.first + s.second, s.first + t.first + t.second)
                     < max(t.first + t.second, t.first + s.first + s.second);
            });

        uint32_t t = 0;
        for (uint32_t i = 0, s = 0; i < soldiers.size(); s += soldiers[i++].first)
            t = max(s + soldiers[i].first + soldiers[i].second, t);
        cout << "Case " << cn << ": " << t << endl;
    }

    return 0;
}
