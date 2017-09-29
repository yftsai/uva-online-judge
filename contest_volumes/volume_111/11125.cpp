// #dynamic_programming
#include <iostream>
#include <map>
#include <numeric>
using namespace std;

int main()
{
    // used_marble_count -> first_group -> last_group -> marble_counts -> arrangment_counts
    map<uint16_t, uint32_t> counts[29][32][32];
    counts[0][0][0][0] = 1;
    for (uint16_t used = 0; used < 28; used++)
        for (uint8_t first_group = 0; first_group < 32; first_group++)
            for (uint8_t last_group = 0; last_group < 32; last_group++)
                for (const auto &p: counts[used][first_group][last_group])
                    for (uint8_t color = 0; color < 4; color++) {
                        const uint8_t first_size = (first_group & 7);
                        const uint8_t last_color = (last_group >> 3), last_size = (last_group & 7);
                        const uint8_t mc = (p.first >> (3 * color)) & 7;

                        for (int size = 1; size <= min(3, 7 - mc); size++) {
                            if (first_size == 0 || (last_color != color && last_size != size)) {
                                uint8_t lg = (color << 3) | size;
                                uint8_t fg = (first_size == 0)  ? lg : first_group;
                                uint16_t mcs = p.first - (mc << (3 * color)) + ((mc + size) << (3 * color));

                                if (counts[used + size][fg][lg].count(mcs) == 0)
                                    counts[used + size][fg][lg][mcs] = p.second;
                                else
                                    counts[used + size][fg][lg][mcs] += p.second;

                            }
                        }
                    }

    uint16_t t, n;
    for (cin >> t; t > 0; t--) {
        cin >> n;
        uint16_t ms[4];
        for (uint16_t i = 0; i < n; i++)
            cin >> ms[i];

        const uint16_t marble_count = accumulate(ms, ms + n, 0);
        uint16_t marble_counts = 0;
        for (auto i = 0; i < n; i++)
            marble_counts |= ms[i] << (3 * i);

        uint32_t count = 0;
        for (uint8_t first_group = 0; first_group < 8 * n; first_group++)
            for (uint8_t last_group = 0; last_group < 8 * n; last_group++)
                for (const auto &p: counts[marble_count][first_group][last_group])
                    if (p.first == marble_counts) {
                        const uint8_t first_color = (first_group >> 3), first_size = (first_group & 7);
                        const uint8_t last_color = (last_group >> 3), last_size = (last_group & 7);
                        if (first_size == marble_count || (first_color != last_color && first_size != last_size))
                            count += p.second;
                    }
        cout << count << endl;
    }

    return 0;
}
