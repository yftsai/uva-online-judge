// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

uint64_t gcd(uint64_t p, uint64_t q)
{
    for (; p % q != 0; swap(p, q))
        p %= q;
    return q;
}

int main()
{
    constexpr uint16_t max_n = 24;

    vector<uint64_t> counts[max_n + 1];
    counts[0].resize(1, 1);
    for (uint16_t dice_count = 0; dice_count < max_n; ++dice_count) {
        counts[dice_count + 1].assign(6 * (dice_count + 1) + 1, 0);

        for (uint16_t s = 1 * dice_count; s <= 6 * dice_count; ++s)
            for (uint16_t i = 1; i <= 6; ++i)
                counts[dice_count + 1][s + i] += counts[dice_count][s];
    }
    for (uint16_t dice_count = 1; dice_count <= max_n; ++dice_count)
        for (uint16_t s = 1; s < counts[dice_count].size(); ++s)
            counts[dice_count][s] += counts[dice_count][s - 1];

    for (uint16_t n, x; cin >> n >> x && n > 0; ) {
        uint64_t q = counts[n].back();
        if (0 < x && x <= 6 * n)
            --x;
        else if (x > 6 * n)
            x = 6 * n;
        uint64_t p = q - counts[n][x];
        const uint64_t d = gcd(p, q);
        p /= d;
        q /= d;

        if (p % q == 0)
            cout << (p / q) << endl;
        else
            cout << p << "/" << q << endl;
    }

    return 0;
}
