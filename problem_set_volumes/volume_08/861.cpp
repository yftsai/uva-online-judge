// #search
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function place returns the number of ways to place k bishops on
// diagonal k, k+2, k+4, ... on a n*n board.
int place(int n, size_t k, int d, vector<pair<int, int>> &bishops)
{
    if (bishops.size() == k)
        return 1;
    else if (bishops.size() + (n*2 - d)/2 < k)
        return 0;
    else {
        int nways = place(n, k, d+2, bishops);
        for (int i= (d<n ? 0 : d-n+1); i < (d<n ? d+1 : n); ++i) {
            auto pred = [d, i](pair<int, int> &p) { return abs(i-p.first) == abs(d-i-p.second); };
            if (find_if(bishops.begin(), bishops.end(), pred) == bishops.end()) {
                bishops.push_back(make_pair(i, d-i));
                nways += place(n, k, d+2, bishops);
                bishops.pop_back();
            }
        }
        return nways;
    }
}

int main()
{
    int n = 8, k=6;
    vector<pair<int, int>> bishops;

    while ((cin >> n >> k) && n>0) {
        int nways = 0;
        for (int i=0; i<=k; ++i)
            nways += place(n, i, 0, bishops) * place(n, k-i, 1, bishops);
        cout << nways << endl;
    }
    return 0;
}
