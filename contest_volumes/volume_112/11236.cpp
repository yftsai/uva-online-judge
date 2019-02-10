#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    auto eliminate_factors = [](int u, int v) {
        while (u % 2 == 0 && v % 2 == 0)
            u /= 2, v /= 2;
        while (u % 5 == 0 && v % 5 == 0)
            u /= 5, v /= 5;
        return u;
    };

    cout.setf(ios::fixed);
    cout.precision(2);
    const int unit_abcd = 100 * 100 * 100;
    for (int ia = 1; ia < int(ceil(100 * pow(20, 0.25))); ++ia) {
        const double a = ia / 100.0;
        const double ub_b = min(pow(20 / a, 1.0 / 3), (a * pow(20 - a, 3) - a) / 3);
        const int unit_bcd = eliminate_factors(unit_abcd, ia);

        for (int ib = ia; ib <= int(ub_b * 100) + 1; ++ib) {
            const double b = ib / 100.0;
            const double ub_c = min(pow(20 / a / b, 1.0 / 2), (a * b * pow(20 - a - b, 2) - a - b) / 2);
            const int unit_cd = eliminate_factors(unit_bcd, ib);

            for (int ic = ib; ic <= int(ub_c * 100) + 1; ++ic) {
                const double c = ic / 100.0;
                const double ub_d = min(20 / a / b / c, a * b * c * (20 - a - b - c) - a - b - c);
                int unit_d = eliminate_factors(unit_cd, ic);

                for (int id = (ic + unit_d - 1) / unit_d * unit_d; id <= int(ub_d * 100) + 1; id += unit_d)
                    if (int64_t(1000 * 1000) * (ia + ib + ic + id) == int64_t(ia) * ib * ic * id)
                        cout << a << " " << b << " " << c << " " << (id / 100.0) << endl;
            }
        }
    }
    return 0;
}
