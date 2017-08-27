// #arithmetic
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n, k;
    for (cin >> n; n>0; n--){
        cin >> k;
        if (k==0)
            cout << 3 << endl;
        else {
            k = (k < 0) ? -k : k;
            int m = int(sqrt(8.0*k + 1)/2);
            for (int s = (m%2 == 0) ? m/2*(m+1) : (m+1)/2*m; s < k || (s-k) % 2 == 1; s += (++m))
                ;
            cout << m << endl;
        }
        if (n>1)
            cout << endl;
    }

    return 0;
}
