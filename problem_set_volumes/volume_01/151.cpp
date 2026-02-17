#include <cstdint>
#include <iostream>
using namespace std;

int main()
{
    for (uint16_t n; cin >> n && n != 0; ) {
        uint32_t m = 0, preds, succs;
        do {
            m++;
            preds = 12;
            succs = n - 13;
            for (uint16_t k = 0; k != preds; k = (k + m - 1) % (preds + succs + 1))
                if (k < preds)
                    preds--;
                else
                    succs--;
        } while (preds > 0 || succs > 0);

        cout << m << endl;
    }

    return 0;
}
