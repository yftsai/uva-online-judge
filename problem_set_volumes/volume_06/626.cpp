// #easy
#include <iostream>
#include <vector>
#include <set>
using namespace std;

void print_chains(const vector<set<int>> &relations, int s, vector<int> &chain, int &total)
{
    if (chain.size() == 2) {
        if (((chain[0] < chain[1] && chain[1] < s) || (chain[0] > chain[1] && chain[1] > s))
            && relations[s].find(chain[0]) != relations[s].end()) {
            cout << (chain[0] + 1) << " " << (chain[1] + 1) << " " << (s + 1) << endl;
            total++;
        }
    }
    else {
        chain.push_back(s);
        for (int prey: relations[s])
            print_chains(relations, prey, chain, total);
        chain.pop_back();
    }
}

int main()
{
    int i, j;
    for (int n; cin >> n; ) {
        vector<set<int>> relations(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                char relation;
                cin >> relation;
                if (relation == '1')
                    relations[i].insert(relations[i].end(), j);
            }

        int total = 0;
        vector<int> chain;
        for (i=0; i<n; i++)
            print_chains(relations, i, chain, total);
        cout << "total:" << total << endl;
        cout << endl;
    }

    return 0;
}
