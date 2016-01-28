#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int l, g, x, r;
    while ((cin >> l >> g) && l!=0) {
        vector<pair<int, int>> intv;
        intv.resize(g);
        for (auto &p: intv) {
            cin >> x >> r;
            p = make_pair(x>=r ? (x-r) : 0, (x+r)<=l ? x+r : l);
        }

        int nremain = 0, loc = 0;
        sort(intv.begin(), intv.end());
        for (int i=0, maxl; i<int(intv.size()) && intv[i].first<=loc && loc<l; loc = maxl, ++nremain)
            for (maxl = loc; i<int(intv.size()) && intv[i].first <= loc; ++i)
                maxl = max(maxl, intv[i].second);

        cout << (loc<l ? -1 : (g - nremain)) << endl;
    }
    return 0;
}
