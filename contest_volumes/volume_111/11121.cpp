#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int ncase, n;

    cin >> ncase;
    for (int i=1; i<=ncase; i++){
        string rep;
        cin >> n;
        for (int base = 1; n!=0; base*=-2){
            if (n%(base*-2)==0)
                rep.append("0");
            else {
                rep.append("1");
                n -= base*1;
            }
        }
        if (rep == "")
            rep = "0";
        reverse(rep.begin(), rep.end());
        cout << "Case #" << i << ": " << rep << endl;
    }

    return 0;
}
