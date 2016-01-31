#include <iostream>
using namespace std;

int main()
{
    int t, l, w, h;
    cin >> t;
    for (int i=1; i<=t; i++) {
        cin >> l >> w >> h;
        cout << "Case " << i << ": " << ((l<=20 && w<=20 && h<=20) ? "good" : "bad") << endl;
    }
    return 0;
}
