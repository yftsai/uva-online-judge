// #easy #cycle_detection
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;

uint16_t next(bitset<9> g)
{
    bitset<9> h;
    for (uint16_t i = 0; i < 9; ++i)
        if (g.test(i)) {
            if (i % 3 > 0)
                h.flip(i - 1);
            if (i % 3 + 1 < 3)
                h.flip(i + 1);

            if (i / 3 > 0)
                h.flip(i - 3);
            if (i / 3 + 1 < 3)
                h.flip(i + 3);
        }
    return h.to_ulong();
}

int main()
{
    bitset<512> is_visited;
    const int16_t unknown = 512;
    int16_t max_indexes[512];
    fill(max_indexes, max_indexes + 512, unknown);

    for (uint16_t g = 0; g < 512; ++g)
        if (!is_visited[g]) {
            uint16_t f = g;
            for (; !is_visited.test(f); f = next(f))
                is_visited.set(f);

            if (max_indexes[f] == unknown)
                for (; max_indexes[f] != -1; f = next(f))
                    max_indexes[f] = -1;

            if (max_indexes[g] == unknown) {
                int16_t max_index = 0;
                for (f = g; max_indexes[f] == unknown; f = next(f), ++max_index)
                    ;
                max_index += max_indexes[f];

                for (f = g; max_indexes[f] == unknown; f = next(f))
                    max_indexes[f] = max_index--;
            }
        }

    uint32_t test_count;
    for (cin >> test_count; test_count > 0; --test_count) {
        bitset<9> g;
        for (char i = 0, c; i < 9 && cin >> c; ++i)
            if (c == '1')
                g.set(i);

        cout << max_indexes[g.to_ulong()] << endl;
    }

    return 0;
}
