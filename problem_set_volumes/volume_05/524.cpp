#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main()
{
    vector<bool> is_prime(32, true);
    is_prime[0] = is_prime[1] = false;
    for (int i=3; i<=31; ++i)
        for (int j=2; j<i && is_prime[i]; ++j)
            if (i%j==0)
                is_prime[i] = false;

    vector<vector<vector<int>>> ring(17);
    for (int n=2; n<=16; n+=2){
        vector<int> r(n);
        iota(r.begin(), r.end(), 1);

        do {
            int p = 0;
            for (; p<n-1 && is_prime[ r[p]+r[p+1] ]; ++p)
                ;

            if (p==n-1 && is_prime[ r[n-1] + r[0] ])
                ring[n].push_back(r);
            else if (p<n-1)
                sort(r.begin()+p+2, r.end(), greater<int>());
        } while (next_permutation(r.begin()+1, r.end()));
    }

    for (int i=1, n; cin >> n; i++) {
        cout << (i==1 ? "" : "\n") << "Case " << i << ":" << endl;
        for (const auto &r: ring[n]) {
            for (auto v: r)
                cout << (v==*r.begin() ? "" : " ") << v;
            cout << endl;
        }
    }

    return 0;
}
