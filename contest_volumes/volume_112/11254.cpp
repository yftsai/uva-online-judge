// #easy
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> sums(1, 1);
    for (int32_t i = 2; sums.back() + i < 1000 * 1000 * 1000; i++)
        sums.push_back(sums.back() + i);

    for (int n; cin >> n && n > 0; ) {
        uint16_t len;
        auto it = upper_bound(sums.begin(), sums.end(), n);
        while (true) {
            --it;
            len = it - sums.begin() + 1;
            if ((n - *it) % len == 0)
                break;
        }
        int start = (n - sums[len - 1]) / len + 1;
        cout << n << " = " << start << " + ... + " << (start + len - 1) << endl;
    }
    return 0;
}
