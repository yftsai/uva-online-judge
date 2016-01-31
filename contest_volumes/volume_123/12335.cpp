#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

string reverse(string s, uint64_t k)
{
    if (k==0)
        return s;
    else {
        size_t len = s.length();
        uint64_t n=1, f=1, m;
        for (; k/f>=(n+1); f*=++n)
            ;
        m = k/f;
        s = reverse(s, k-m*f);
        s = s.substr(0, len-n-1) + s.substr(len-n, m) + s[len-n-1] + s.substr(len-n+m, n-m);
        return s;
    }
}

int main()
{
    int t;
    cin >> t;
    for (int i=1; i<=t; i++) {
        uint64_t k;
        string s;
        cin >> s >> k;
        s = reverse(s, k-1);
        cout << "Case " << i << ": " << s << endl;
    }

    return 0;
}
