// #longest_increasing_subsequence
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<pair<uint16_t, uint16_t>> events;
    vector<uint16_t> ends;

    uint16_t n;
    for (cin >> n; n > 0; n--) {
        events.clear();

        for (uint16_t s, f; cin >> s >> f && f != 0; )
            events.emplace_back(s, f);
        sort(events.begin(), events.end());

        ends.clear();
        for (const auto &e: events) {
            auto it = lower_bound(ends.begin(), ends.end(), e.first + 1);
            if (it == ends.end())
                ends.push_back(e.second);
            else if (e.second < *it)
                *it = e.second;
        }
        cout << ends.size() << endl;
    }

    return 0;
}
