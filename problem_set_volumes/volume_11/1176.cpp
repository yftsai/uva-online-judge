#include <iostream>
#include <cstdint>
using namespace std;

int main()
{
    for (uint16_t n; cin >> n; ) {
        // The algorithm to find the survivor is extended from "Concrete Mathematics."
        uint16_t bit_count = 0;
        for (uint16_t m = n; m != 0; bit_count++)
            m = m & (m - 1);        // clears the rightmost bit
        uint16_t survivor = (1 << bit_count) - 1;

        cout << (n - survivor + 2 * survivor) << endl;
    }

    return 0;
}
