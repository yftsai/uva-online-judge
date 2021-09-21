// #longest_increasing_sequence
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    uint16_t t, m;
    typedef pair<uint16_t, uint16_t> doll_t;
    vector<doll_t> dolls;

    for (cin >> t; t > 0 && cin >> m; t--) {
        dolls.resize(m);
        for (auto &d: dolls)
            cin >> d.first >> d.second;

        sort(dolls.begin(), dolls.end(),
            [](const doll_t &d, const doll_t &e)
            {
                if (d.first != e.first)
                    return d.first < e.first;
                else
                    return d.second > e.second;
            });

        multiset<uint16_t> heights;
        for (const auto &d: dolls) {
            auto it = heights.lower_bound(d.second);
            if (it != heights.begin())
                it = heights.erase(prev(it));
            heights.insert(it, d.second);
        }
        cout << heights.size() << endl;
    }

    return 0;
}
