// #combinatorics
#include <iostream>
#include <memory>
using namespace std;

int main()
{
    const uint16_t max_n = 100;
    const uint32_t limit = 1000 * 1000;

    unique_ptr<uint32_t[]> ptriangle[1 + max_n];
    auto choose = [&](uint16_t n, uint16_t r) -> uint64_t { return ptriangle[n][min<uint16_t>(r, n - r)]; };
    for (uint16_t n = 0; n <= max_n; n++) {
        ptriangle[n].reset(new uint32_t[1 + n/2]);
        ptriangle[n][0] = 1;
        for (uint16_t r = 1; r <= n/2; r++)
            ptriangle[n][r] = (choose(n - 1, r - 1) + choose(n - 1, r)) % limit;
    }

    for (uint16_t n, k; cin >> n >> k && n != 0; ) {
        uint32_t count = 0;
        for (uint16_t zero_count = (k >= n) ? (k - n) : 0; zero_count < k; zero_count++)
            count = (count + choose(k, zero_count) * choose(n - 1, k - zero_count - 1)) % limit;
        cout << count << endl;
    }
    return 0;
}
