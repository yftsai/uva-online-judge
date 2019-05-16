// #geometry
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    const double pi = acos(-1);
    cout.setf(ios::fixed);
    cout.precision(3);

    uint16_t n, d, l;
    for (cin >> n; n > 0 && cin >> d >> l; --n) {
        double a = l / 2.0;
        double b = sqrt(pow(l / 2.0, 2) - pow(d / 2.0, 2));
        cout << pi * a * b << endl;
    }

    return 0;
}
