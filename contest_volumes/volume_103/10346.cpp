// #trivial
#include <iostream>
using namespace std;

int main()
{
    for (uint32_t n, k; cin >> n >> k; ) {
        uint32_t count = 0;
        for (uint32_t ccount = n, bcount = 0; ccount > 0; ccount = bcount / k, bcount = bcount % k) {
            count += ccount;
            bcount += ccount;
        }
        cout << count << endl;
    }

    return 0;
}
