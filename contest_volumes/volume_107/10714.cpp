#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int c, l, n;

    for(cin >> c; c>0; c--){
        int p, earliest=0, latest=0;

        cin >> l >> n;
        for (int i=0; i<n; i++){
            cin >> p;
            earliest = max(earliest, min(p, l-p));
            latest = max(latest, max(p, l-p));
        }
        cout << earliest << " " << latest << endl;
    }

    return 0;
}
