// #easy
#include <iostream>
using namespace std;

int main()
{
    uint16_t t;
    uint32_t n;

    cin >> t;
    for (uint16_t case_number = 1; case_number <= t && cin >> n; ++case_number) {
        uint32_t k = 0;

        for (uint32_t i = 0, g = 0, current_k = k, h; i < n && cin >> h; ++i, g = h) {
            if (h - g > current_k) {
                k = max(k + 1, h - g);
                current_k = (k == h - g) ? k - 1 : k;
            }
            else if (h - g == current_k)
                --current_k;
        }

        cout << "Case " << case_number << ": " << k << endl;
    }

    return 0;
}
