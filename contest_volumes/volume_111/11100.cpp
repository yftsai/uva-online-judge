// #easy
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    bool is_first = true;
    for (int n = 0; (cin >> n) && n != 0; ) {
        vector<int> bags(n), inner_bag_indexes(n);
        for (auto &b: bags)
            cin >> b;
        sort(bags.begin(), bags.end());

        set<pair<size_t, size_t>> pieces;   // bag count, inner bag index
        for (size_t i = 0, j; i < bags.size(); i+=j) {
            set<pair<size_t, size_t>> ps;
            for (j=0; i+j < bags.size() && bags[i] == bags[i+j]; j++) {
                if (pieces.size() == 0)
                    ps.insert(pair<size_t, size_t>(1, i + j));
                else {
                    auto it = pieces.begin();
                    inner_bag_indexes[i+j] = it->second;
                    ps.insert(pair<size_t, size_t>(it->first+1, i+j));
                    pieces.erase(it);
                }
            }
            pieces.insert(ps.begin(), ps.end());
        }

        if (is_first)
            is_first = false;
        else
            cout << endl;
        cout << pieces.size() << endl;
        for (const auto &p: pieces) {
            for (size_t i = 0, j = p.second; i < p.first; i++, j = inner_bag_indexes[j])
                cout << (i == 0 ? "" : " ") << bags[j];
            cout << endl;
        }
    }

    return 0;
}
