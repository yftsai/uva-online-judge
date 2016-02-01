#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool operator<=(string &nl, string &nr)
{
    if (nl.length() > nr.length())
        return false;
    else if (nl.length() < nr.length())
        return true;
    else
       return !(nl > nr);
}

int fact(int n)
{
    int c = 1;
    for (int i=2; i<=n; ++i)
        c *= i;
    return c;
}

int count(string c, size_t n, vector<string> &f)
{
    int cnt = 0;
    if (c.length()==0 || c[0] == '0')
        ;
    else if (n>1 && !(f[n-2]<=f[n-1]))
        ;
    else if (n>0 && !(f[n-1]<=c))
        ;
    else if (n == f.size()-1) {
        const int nprime = 9;
        f[n] = c;
        cnt = fact(nprime)/fact(nprime - f.size());
        for (size_t i=0, j; i<f.size(); i+=j, cnt/=fact(j))
            for (j=1; i+j<f.size() && f[i]==f[i+j]; ++j)
                ;
    }
    else
        for (int i=n>0 ? f[n-1].length() : 1; (f.size()-n-1)*i<=c.length()-i; ++i) {
            f[n] = c.substr(0, i);
            cnt += count(c.substr(i), n+1, f);
        }
    return cnt;
}

int main()
{
    int t;
    string c;
    for (cin >> t; t>0 && cin >> c; t--)
        if (c[0] == '0')
            cout << 1 << endl;
        else {
            int n = c[0] - '0';
            vector<string> freq(n);
            cout << count(c.substr(1), 0, freq) << endl;
        }

    return 0;
}
