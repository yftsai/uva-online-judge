// #easy
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    for (uint32_t n; cin >> n && n > 0; ) {
        uint32_t max_qsz = 0, max_i, w, h;
        for (uint32_t i = 1; i <= n && cin >> w >> h; ++i) {
            if (w < h)
                swap(w, h);

            uint32_t qsz = max(min(w, h * 4u), min(w * 2u, h * 2u));
            if (qsz > max_qsz) {
                max_i = i;
                max_qsz = qsz;
            }
        }

        cout << max_i << endl;
    }

    return 0;
}
