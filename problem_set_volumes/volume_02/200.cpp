// #topological_sort
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    string items[2];
    map<char, set<char>> lt_chars;
    if (cin >> items[0] && items[0] != "#")
        for (; cin >> items[1] && items[1] != "#"; swap(items[0], items[1])) {
            size_t len = min(items[0].size(), items[1].size());
            auto positions = mismatch(items[0].begin(), items[0].begin() + len, items[1].begin());
            if (positions.first != items[0].end() && positions.second != items[1].end())
                lt_chars[*positions.first].insert(*positions.second);
        }

    map<char, uint16_t> gt_counts;
    set<pair<uint16_t, char>> queue;

    for (const auto &p: lt_chars) {
        const char c = p.first;
        auto it = gt_counts.lower_bound(c);
        if (it == gt_counts.end() || it->first != c)
            gt_counts.emplace_hint(it, c, 0);
        for (const char d: p.second) {
            it = gt_counts.lower_bound(d);
            if (it == gt_counts.end() || it->first != d)
                gt_counts.emplace_hint(it, d, 1);
            else
                ++it->second;
        }
    }
    for (const auto &p: gt_counts)
        queue.emplace(p.second, p.first);

    while (!queue.empty()) {
        const char c = queue.begin()->second;
        queue.erase(queue.begin());
        cout << c;
        for (const char d: lt_chars[c]) {
            queue.erase(pair<uint16_t, char>(gt_counts[d], d));
            queue.emplace(--gt_counts[d], d);
        }
    }
    cout << endl;

    return 0;
}
