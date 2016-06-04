#include <iostream>
using namespace std;

int main()
{
    int ncases, n;

    for (cin >> ncases; ncases>0 && cin >> n; ncases--) {
        int count[10];
        for (int i=0; i<10; i++)
            count[i] = 0;

        for (int base=1; base<=n; base*=10) {
            const int v[3] = { n%base, (n/base)%10, n/base/10};
    
            if (v[2]>0) {
                // counting 0's when v[2] below it's current value
                count[0] += (v[2]-1)*base;
                // coutning 0's when v[2] at it's current value
                count[0] += (v[1]==0) ? (v[0]+1) : base;
            }

            for (int i=1; i<10; i++) {
                // counting i when v[2] below it's current value
                count[i] += v[2]*base;

                // counting i when v[2] at it's current value
                if (i<v[1])
                    count[i] += base;
                else if (i==v[1])
                    count[i] += v[0] + 1;
            }
        }

        for (int i=0; i<10; i++)
            cout << (i==0 ? "" : " ") << count[i];
        cout << endl;
    }

    return 0;
}
