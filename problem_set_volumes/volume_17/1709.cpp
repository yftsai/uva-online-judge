#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout.setf(ios::fixed);
    cout.precision(6);
    for (int p, a, b, c, d, n; cin >> p >> a >> b >> c >> d >> n; ) {
        double max_p = -3, max_d = 0;
        for (int akb = a + b, ckd = c + d; n > 0; n--, akb += a, ckd += c) {
            double p = sin(akb) + cos(ckd);
            max_p = max(max_p, p);
            max_d = max(max_d, max_p - p);
        }
        cout << p * max_d << endl;
    }

    return 0;
}
