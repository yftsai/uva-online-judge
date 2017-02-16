// #trivial
#include <iostream>
using namespace std;

int getBinCount(int v)
{
    int c=0;
    for (; v>0; v/=2)
        c+=v%2;
    return c;
}

int getHexCount(int v)
{
    int c=0;
    for (; v>0; v/=10){
        int d=v%10;
        for (; d>0; d/=2)
            c+=d%2;
    }
    return c;
}

int main()
{
    int n, m;

    for (cin >> n; n>0; n--){
        cin >> m;
        cout << getBinCount(m) << " " << getHexCount(m) << endl;
    }

    return 0;
}
