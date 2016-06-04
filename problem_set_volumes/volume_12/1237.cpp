#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>
using namespace std;
        
int main()
{
    bool first = true;
    int t, d, l, h, p, q;
    for (cin >> t; t>0; t--, first = false) {
        const int UNKNOWN = INT_MAX;
        map<pair<int, int>, int> intv_maker;    // only maintains the region where there is no or one maker
        vector<string> maker;

        intv_maker.emplace(make_pair(INT_MIN, INT_MAX), UNKNOWN);
        for (cin >> d; d>0; d--) {
            string m;
            cin >> m >> l >> h;
            maker.push_back(m);

            map<pair<int, int>, int> tmp;
            auto j = intv_maker.upper_bound(make_pair(h, INT_MAX));
            auto i = j;     // i points to an overlapped region when i!=j
            while (i!=intv_maker.begin() && prev(i)->first.second >= l) {
                const pair<int, int> &intv = (--i)->first;
                // update the overlapped part
                if (i->second == UNKNOWN)
                    tmp.emplace(make_pair(max(intv.first, l), min(intv.second, h)), maker.size()-1);
                // leave the non-overlapped parts intact
                if (intv.first < l)
                    tmp.emplace(make_pair(intv.first, l-1), i->second);
                if (intv.second > h)
                    tmp.emplace(make_pair(h+1, intv.second), i->second);
            }
            intv_maker.erase(i, j);
            intv_maker.insert(tmp.begin(), tmp.end());
        }

        if (!first)
            cout << endl;
        for (cin >> q; q>0; q--) {
            cin >> p;
            auto it = intv_maker.upper_bound(make_pair(p, INT_MAX));
            if (it==intv_maker.begin() || prev(it)->first.second < p || prev(it)->second==UNKNOWN)
                cout << "UNDETERMINED" << endl;
            else
                cout << maker[prev(it)->second] << endl;
        }
    }

    return 0;
}
