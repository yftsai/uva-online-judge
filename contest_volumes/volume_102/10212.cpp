#include <iostream>
using namespace std;

int main()
{
    for (int n, m; cin >> n >> m; ) {
        int p = 1, e2 = 0, e5 = 0;
        for (int i=n; i>(n-m); --i) {
            int j = i;
            for (; j%10==0; j/=10)
                ;
            for (; j%2==0; j/=2)
                if (e5 > 0)
                    --e5;
                else
                    ++e2;
            for (; j%5==0; j/=5)
                if (e2 > 0)
                    --e2;
                else
                    ++e5;

            p=(p*j)%10;
        }

        for (int i=0; i<e2; ++i)
            p = (p*2)%10;
        for (int i=0; i<e5; ++i)
            p = (p*5)%10;
        
        cout << p << endl;
    }
    return 0;
}
