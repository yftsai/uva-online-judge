#include <iostream>
#include <cstdint>
using namespace std;

int main()
{
    uint32_t ncases;
    cin >> ncases;

    for (uint16_t cno = 1, n; cno <= ncases && cin >> n; cno++) {
        // The algorithm is based on "Concrete Mathematics."
        uint16_t msb = 1u << 14, rep = 0;
        while (msb > n)
            msb >>= 1;
        for (uint16_t m; (m = ((n - msb) << 1) + 1) != n; n = m, rep++)
            while (msb > m)
                msb >>= 1;

        cout << "Case " << cno << ": " << rep << " " << n << endl;
    }

    return 0;
}
