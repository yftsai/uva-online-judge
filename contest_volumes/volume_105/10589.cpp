// #floating_point
#include <iostream>
using namespace std;

int64_t sq_sum(int32_t x, int32_t y)
{
    return int64_t(x) * x + int64_t(y) * y;
}

int main()
{
    const int32_t ibase = 1000 * 1000 * 10;
    cout.setf(ios::fixed);
    cout.precision(5);

    for (int32_t n, a; cin >> n >> a && n != 0; ) {
        a *= ibase;
        const int64_t asq = int64_t(a) * a;

        int32_t xi, xf, yi, yf;
        char xdot, ydot;
        int32_t m = 0;
        for (int32_t i = 0; i < n && cin >> xi >> xdot >> xf >> yi >> ydot >> yf; ++i) {
            const int32_t x = ibase * xi + xf;
            const int32_t y = ibase * yi + yf;
            if (!(sq_sum(x, y) > asq
                || sq_sum(x, a - y) > asq
                || sq_sum(a - x, y) > asq
                || sq_sum(a - x, a - y) > asq))
                ++m;
        }

        cout << double(asq / ibase / ibase * m) / n << endl;
    }

    return 0;
}
