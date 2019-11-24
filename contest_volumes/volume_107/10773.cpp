// #easy
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout.setf(ios::fixed);
    cout.precision(3);
    uint32_t test_count;
    cin >> test_count;
    for (uint16_t test_number = 1; test_number <= test_count; ++test_number) {
        double d, v, u;
        cin >> d >> v >> u;
        cout << "Case " << test_number << ": ";
        if (u <= 0 || v <= 0 || u <= v)
            cout << "can't determine" << endl;
        else
            cout << (d / sqrt(u * u - v * v) - d / u) << endl;
    }

    return 0;
}
