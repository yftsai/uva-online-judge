// #depth-first-search
// This solution is a credit to naivered.github.io, but it is not scalable to more difficult inputs.
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

typedef pair<int, bool> part;   // length, is_available

bool compose(const int length, vector<part> &parts, size_t index = 0, int partial = 0)
{
    bool is_composable = false;
    if (index == 0 || partial == length) {
        auto pred_avail = [](const part &p) { return p.second; };
        auto it = find_if(parts.begin(), parts.end(), pred_avail);
        if (it == parts.end())
            is_composable = true;
        else {
            it->second = false;
            is_composable = compose(length, parts, it - parts.begin() + 1, it->first);
            it->second = true;
        }
    }
    else
        for (; index < parts.size(); ++index)
            if (parts[index].second && partial + parts[index].first <= length
                && (parts[index - 1].first != parts[index].first || !parts[index - 1].second)) {
                parts[index].second = false;
                is_composable = compose(length, parts, index + 1, partial + parts[index].first);
                parts[index].second = true;

                // The selection of a part to finish a single stick always starts with the most
                // restricted choice, relaxing it won't help.
                if (is_composable || partial + parts[index].first == length)
                    break;
            }
    return is_composable;
}

int main()
{
    for (int n; cin >> n && n > 0; ) {
        vector<part> parts(n, part(0, true));
        for (auto &p: parts)
            cin >> p.first;

        sort(parts.begin(), parts.end(), greater<part>());
        auto add = [](const part &p1, const part &p2) { return part(p1.first + p2.first, false); };
        int total = accumulate(parts.begin(), parts.end(), part(0, false), add).first;

        for (int length = parts[0].first; ; ++length)
            if (total % length == 0 && compose(length, parts)) {
                cout << length << endl;
                break;
            }
    }

    return 0;
}
