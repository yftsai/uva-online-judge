// #set_union
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> centers;
    vector<uint32_t> lengths;

    uint32_t t, n;
    for (cin >> t; t > 0 && cin >> n; t--, lengths.clear()) {
        centers.resize(n);
        iota(centers.begin(), centers.end(), 0);
        lengths.resize(n, 0);

        char cmd;
        while (cin >> cmd && cmd != 'O') {
            uint16_t i, j;
            if (cmd == 'E') {
                cin >> i;
                uint32_t length = 0;
                uint16_t c = i - 1;
                for (; centers[c] != c; c = centers[c])
                    length += lengths[c];
                cout << length << endl;

                for (uint16_t d = i - 1, e; centers[d] != c; d = e) {
                    e = centers[d];
                    centers[d] = c;

                    uint32_t len = length - lengths[d];
                    lengths[d] = length;
                    length = len;
                }
            }
            else {
                cin >> i >> j;
                lengths[i - 1] = (i >= j) ? (i - j) : (j - i);
                lengths[i - 1] %= 1000;
                centers[i - 1] = j - 1;
            }
        }
    }
    return 0;
}
