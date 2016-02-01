#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
    for (int n; cin >> n && n>0; ) {
        vector<int> a(n);
        for (auto &ai: a)
            cin >> ai;

        vector<bool> start(n, true);
        for (int i=0, sum=0, p=0; i<2*n; ++i, p=(p-1+n)%n)
            if ((sum = min(a[p], sum+a[p])) < 0)
                start[p] = false;
        
        int nshift = 0;
        for (auto b: start)
            if (b)
                ++nshift;
        cout << nshift << endl;
    }

    return 0;
}
