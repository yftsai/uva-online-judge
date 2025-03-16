// #trivial
#include <iostream>
using namespace std;

int main()
{
    for (uint16_t t; cin >> t && t > 0; ) {
        uint32_t max_lw = 0;
        uint16_t max_h = 0;
        for (uint16_t i = 0, l, w, h; i < t && cin >> l >> w >> h; i++)
            if (h > max_h || (h >= max_h && l * w > max_lw)) {
                max_lw = l * w;
                max_h = h;
            }

        cout << (max_lw * max_h) << endl;
    }
    return 0;
}
