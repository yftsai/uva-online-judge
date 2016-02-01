#include <iostream>
#include <vector>
using namespace std;

vector<int> factor(int v)
{
    vector<int> digit;
   
    if (v==0)
        digit.push_back(0);
    else if (v==1)
        digit.push_back(1);
    else {
        for (int d=9; d>=2; d--)
            for (; v%d==0; v/=d)
                digit.push_back(d);
        if (v!=1)
            digit.push_back(v);
    }

    return digit;
}

int main()
{
    int ncase;

    for (cin >> ncase; ncase>0; ncase--){
        int n;
        cin >> n;
        vector<int> digit = factor(n);
        if (digit.back() > 9)
            cout << -1 << endl;
        else {
            for (vector<int>::const_reverse_iterator it = digit.rbegin(); it!=digit.rend(); it++)
                cout << *it;
            cout << endl;
        }
    }

    return 0;
}
