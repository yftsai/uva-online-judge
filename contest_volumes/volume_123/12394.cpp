#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main()
{
    for (int k, n; cin >> k >> n && k!=0; ) {
        vector<string> auth_inst(n);
        vector<vector<int>> pap_rev(n);
        for (int auth=0; auth<n && cin >> auth_inst[auth]; ++auth)
            for (int j=0, p; j<k && cin >> p; ++j)
                pap_rev[p-1].push_back(auth);

        int nproblem = 0;
        for (int i=0; i<n; ++i) {
            bool valid = (pap_rev[i].size() == k);
            set<int> reviewer;
            for (auto it = pap_rev[i].begin(); it != pap_rev[i].end() && valid; ++it)
                if (valid = (reviewer.find(*it) == reviewer.end()))
                    reviewer.insert(*it);

            for (auto it = pap_rev[i].begin(); it != pap_rev[i].end() && valid; ++it)
                valid = (auth_inst[*it] != auth_inst[i]);

            if (!valid)
                ++nproblem;
        }

        if (nproblem == 0)
            cout << "NO PROBLEMS FOUND" << endl;
        else if (nproblem == 1)
            cout << "1 PROBLEM FOUND" << endl;
        else
            cout << nproblem << " PROBLEMS FOUND" << endl;
    }
    
    return 0;
}
