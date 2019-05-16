#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<uint16_t> years;
    vector<uint32_t> ns;

    uint32_t factorial_ubound = 2;
    double e = 0;
    for (uint32_t y = 1969, bit_count = 4; y <= 2169; y += 10, bit_count *= 2) {
        for (; e < bit_count; ++factorial_ubound)
            e += log2(factorial_ubound);
        years.push_back(y);
        ns.push_back(factorial_ubound - 2);
    }

    for (uint16_t y; cin >> y && y > 0; )
        cout << ns[lower_bound(years.begin(), years.end(), y) - years.begin()] << endl;

    return 0;
}
