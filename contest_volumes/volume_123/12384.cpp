#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    vector<int> prime, x, s;
    for (int i=2; prime.size()<100000 ; i++) {
        bool is_prime = true;
        for (size_t j = 0; is_prime && j<prime.size() && prime[j] <= sqrt(i); j++)
            is_prime = (i % prime[j]) != 0;
        if (is_prime)
            prime.push_back(i);
    }

    int t, n, m;
    for (cin >> t; t>0; t--) {
        cin >> n >> m;
        x.resize(n);
        s.resize(n);

        for (int i=0; i<n; i++)
            x[i] = prime[i]%m;

        s[0] = 1;
        for (int i=1; i<n; i++) {
            int j = i-1;
            for (; j>=0 && x[j]<=x[i]; j = j-s[j])
                ;
            s[i] = i-j;
        }

        int v = 0;
        for (auto i : s)
            v = (v+i)%m;
        cout << v << endl;
    }

    return 0;
}
