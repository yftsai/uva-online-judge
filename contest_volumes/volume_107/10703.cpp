#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    for (uint16_t w, h, n; cin >> w >> h >> n && w > 0; ) {
        map<uint16_t, map<uint16_t, uint16_t>> spots;
        spots[1][1] = h;
        spots[w + 1u];

        for (uint16_t i = 0, x1, y1, x2, y2; i < n && cin >> x1 >> y1 >> x2 >> y2; ++i) {
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);

            uint16_t x3 = x2 + 1u;
            auto xit = spots.lower_bound(x3);
            if (xit->first > x3)
                spots.emplace_hint(xit, x3, prev(xit)->second);
            xit = spots.lower_bound(x1);
            if (xit == spots.end() || xit->first > x1)
                xit = spots.emplace_hint(xit, x1, prev(xit)->second);

            for (; xit != spots.end() && xit->first <= x2; ++xit) {
                auto &yzs = xit->second;
                auto yit = yzs.lower_bound(y1);
                if ((yit == yzs.end() || yit->first > y1) && yit != yzs.begin())
                    --yit;
                while (yit != yzs.end() && yit->first <= y2) {
                    uint16_t y = yit->first;
                    uint16_t z = yit->second;
                    if (y1 <= z)
                        yit = yzs.erase(yit);
                    else
                        ++yit;

                    if (y < y1)
                        yit = next(yzs.emplace_hint(yit, y, y1 - 1u));
                    if (y2 < z)
                        yit = next(yzs.emplace_hint(yit, y2 + 1u, z));
                }
            }
        }

        uint32_t count = 0;
        for (auto it = spots.begin(); it != spots.end(); ++it) {
            uint16_t x2 = (next(it) == spots.end()) ? w : next(it)->first;
            for (const auto &yz: it->second)
                count += (x2 - it->first) * (yz.second - yz.first + 1u);
        }

        if (count == 0)
            cout << "There is no empty spots." << endl;
        else if (count == 1)
            cout << "There is one empty spot." << endl;
        else
            cout << "There are " << count << " empty spots." << endl;
    }
    return 0;
}
