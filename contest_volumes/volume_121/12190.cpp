// #binary_search
#include <iostream>
using namespace std;

constexpr uint32_t bases[] = {
    2 * 100,
    2 * 100 + 3 * 9900,
    2 * 100 + 3 * 9900 + 5 * 990000
};

uint32_t get_amount(uint32_t e)
{
    if (e <= 100)
        return 2 * e;
    else if (e <= 10 * 1000)
        return bases[0] + 3 * (e - 100);
    else if (e <= 1000 * 1000)
        return bases[1] + 5 * (e - 10 * 1000);
    else
        return bases[2] + 7 * (e - 1000 * 1000);
}

int main()
{
    for (uint32_t a, b; cin >> a >> b && a > 0; ) {
        uint32_t sum;
        if (a <= bases[0])
            sum = a / 2;
        else if (a <= bases[1])
            sum = (a - bases[0]) / 3 + 100;
        else if (a <= bases[2])
            sum = (a - bases[1]) / 5 + 10000;
        else
            sum = (a - bases[2]) / 7 + 1000000;

        uint32_t lb = 1;
        for (uint32_t ub = (sum + 1) / 2, d = a; d != b; ) {
            uint32_t m = (lb + ub) / 2;
            d = get_amount(sum - m) - get_amount(m);
            if (d < b)
                ub = m;
            else if (d == b)
                lb = m;
            else
                lb = m + 1;
        }

        cout << get_amount(lb) << endl;
    }

    return 0;
}
