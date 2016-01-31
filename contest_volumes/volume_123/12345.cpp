#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main()
{
    int n, m;
    vector<int> value, prev;
    map<int, set<int>> loc;

    cin >> n >> m;
    for (int i=0, v; i<n && cin >> v; i++) {
        value.push_back(v);
        auto it = loc[v].rbegin();
        prev.push_back(it == loc[v].rend() ? -1 : *it);
        loc[v].insert(i);
    }

    char op;
    for (int i=0, x, y; i<m && cin >> op >> x >> y; ++i)
        if (op == 'M') {
            int oval = value[x];
            // remove x from the list of old[x]
            set<int> &oloc = loc[oval];
            auto itloc  = oloc.find(x);
            itloc = oloc.erase(itloc);
            // fix the prev of the successor of old[x]
            if (itloc != oloc.end())
                prev[*itloc] = prev[x];
            // add x to the list of y
            set<int> &nloc = loc[y];
            nloc.insert(x);
            // fix the prev of x
            itloc = nloc.find(x);
            prev[x] = itloc == nloc.begin() ? -1 : *(--nloc.find(x));
            // fix prev of the next y value
            ++itloc;
            if (itloc != nloc.end())
                prev[*itloc] = x;
            // assignment
            value[x] = y;
        }
        else {
            int count = 0;
            for (int i = x; i<y; ++i)
                if (prev[i] < x)
                    count++;
            cout << count << endl;
        }

    return 0;
}
