// #priority_queue
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t t;
    vector<string> strs[2];
    typedef pair<uint16_t, uint16_t> concat_str;
    vector<concat_str> concat_strs;
    concat_str last_str;

    auto cmp = [&](const concat_str &s, const concat_str &t)
    {
        const auto &s_left = strs[0][s.first], &s_right = strs[1][s.second];
        const auto &t_left = strs[0][t.first], &t_right = strs[1][t.second];
        const uint16_t s_size = s_left.size() + s_right.size();
        const uint16_t t_size = t_left.size() + t_right.size();
        for (uint16_t i = 0; i < min(s_size, t_size); i++) {
            const char c = i < s_left.size() ? s_left[i] : s_right[i - s_left.size()];
            const char d = i < t_left.size() ? t_left[i] : t_right[i - t_left.size()];
            if (c != d)
                return c < d;
        }

        return s_size < t_size;
    };

    string line;
    getline(cin, line);
    t = stoi(line);
    for (uint16_t case_number = 1, m, n; case_number <= t && getline(cin, line); case_number++) {
        stringstream ss(line);
        ss >> m >> n;

        strs[0].resize(m);
        for (auto &s: strs[0])
            getline(cin, s);

        strs[1].resize(n);
        for (auto &s: strs[1])
            getline(cin, s);

        for (auto &ss: strs)
            sort(ss.begin(), ss.end());

        concat_strs.clear();
        for (uint16_t i = 0; i < strs[0].size(); i++)
            if (strs[1].size() > 0)
                concat_strs.emplace_back(i, strs[1].size() - 1);
        make_heap(concat_strs.begin(), concat_strs.end(), cmp);

        uint32_t count = 0;
        while (concat_strs.size() > 0) {
            pop_heap(concat_strs.begin(), concat_strs.end(), cmp);
            const auto cs = concat_strs.back();

            if (count == 0 || cmp(cs, last_str))
                count++;
            last_str = cs;

            if (cs.second == 0)
                concat_strs.pop_back();
            else {
                concat_strs.back() = concat_str(cs.first, cs.second - 1);
                push_heap(concat_strs.begin(), concat_strs.end(), cmp);
            }
        }

        cout << "Case " << case_number << ": " << count << endl;
    }
}
