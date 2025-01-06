// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint32_t> chocolates[3];
    auto has_more = [&](uint32_t *idxes) {
        for (uint16_t i = 0; i < 3; i++)
            if (idxes[i] < chocolates[i].size())
                return true;
        return false;
    };
    auto get = [&](uint16_t i, uint32_t j) {
        return (j < chocolates[i].size()) ? chocolates[i][j] : 123456;
    };

    uint16_t t;
    cin >> t;
    for (uint16_t cno = 1; cno <= t; cno++) {
        for (uint32_t i = 0, count; i < 3 && cin >> count; i++)
            chocolates[i].resize(count);
        for (auto &cs: chocolates)
            for (auto &c: cs)
                cin >> c;
        for (auto &cs: chocolates) {
            sort(cs.begin(), cs.end());
            cs.erase(unique(cs.begin(), cs.end()), cs.end());
        }

        cout << "Case #" << cno << ":" << endl;
        for (uint32_t i = 0; i < 3; i++) {
            chocolates[0].swap(chocolates[i]);

            uint32_t ucount = 0, lcount = 0;
            uint32_t idxes[3] = { 0 };
            while (has_more(idxes)) {
                auto c0 = get(0, idxes[0]);
                auto c1 = get(1, idxes[1]);
                auto c2 = get(2, idxes[2]);

                if (c0 < c1 && c0 < c2) {
                    ucount++;
                    idxes[0]++;
                }
                else if (c1 < c0 && c1 < c2)
                    idxes[1]++;
                else if (c2 < c0 && c2 < c1)
                    idxes[2]++;
                else if (c0 == c1 && c0 == c2) {
                    idxes[0]++;
                    idxes[1]++;
                    idxes[2]++;
                }
                else if (c0 == c1) {
                    idxes[0]++;
                    idxes[1]++;
                }
                else if (c0 == c2) {
                    idxes[0]++;
                    idxes[2]++;
                }
                else {
                    lcount++;
                    idxes[1]++;
                    idxes[2]++;
                }
            }
            cout << ucount << " " << lcount << endl;

            chocolates[0].swap(chocolates[i]);
        }
    }

    return 0;
}
