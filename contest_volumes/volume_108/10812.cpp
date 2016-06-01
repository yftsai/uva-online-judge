// #trivial
#include <iostream>
using namespace std;

int main()
{
    int n, s, d;

    for (cin >> n; n>0; n--){
        cin >> s >> d;
        if ((s+d)%2!=0 || s<d)
            cout << "impossible" << endl;
        else
            cout << (s+d)/2 << " " << (s-d)/2 << endl;
    }

    return 0;
}
