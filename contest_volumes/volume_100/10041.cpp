#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int cases;
    int r, s[500], dis, i;

    for (cin >> cases; cases>0; cases--){
        cin >> r;
        for (i=0; i<r; i++)
            cin >> s[i];
        sort(s, s+r);
        for (i=0, r--, dis=0; i<r; i++, r--)
            dis+=s[r]-s[i];
        cout << dis << endl;
    }

    return 0;
}
