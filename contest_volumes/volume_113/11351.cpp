#include <iostream>
#include <cstdint>
using namespace std;

int main()
{
    uint16_t case_count;
    cin >> case_count;
    for (uint32_t cno = 1, n, k; cno <= case_count && cin >> n >> k; cno++) {

        uint32_t survivor = 0;
        for (uint32_t i = 2; i <= n; i++)
            survivor = (survivor + k) % i;

        cout << "Case " << cno << ": " << survivor + 1 << endl;
    }

    return 0;
}
