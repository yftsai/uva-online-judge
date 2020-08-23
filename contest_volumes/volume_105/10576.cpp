// #easy
#include <iostream>
using namespace std;

void enumerate(
    const int s, const int d,
    const uint16_t m, const int slice, const int sum,
    int surpluses[12], int &max_surplus)
{
    if (m == 12)
        max_surplus = max(sum, max_surplus);
    else {
        const int t = slice - ((m >= 5) ? surpluses[m - 5] : 0);

        surpluses[m] = s;
        if (m < 4 || t + s < 0)
            enumerate(s, d, m + 1, t + s, sum + s, surpluses, max_surplus);

        surpluses[m] = -d;
        if (m < 4 || t - d < 0)
            enumerate(s, d, m + 1, t - d, sum - d, surpluses, max_surplus);
    }
}

int main()
{
    for (int s, d; cin >> s >> d; ) {
        int surpluses[12];
        int max_surplus = 0;
        enumerate(s, d, 0, 0, 0, surpluses, max_surplus);

        if (max_surplus > 0)
            cout << max_surplus << endl;
        else
            cout << "Deficit" << endl;
    }

    return 0;
}
