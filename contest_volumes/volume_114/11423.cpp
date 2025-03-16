// #binary_indexed_tree
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class lru_cache
{
    private:
        vector<int32_t> bitree;     // binary indexed tree
        vector<uint32_t> seqnums;
        uint32_t seq;

        void update(uint32_t s, int16_t v);
        uint32_t get_count(uint32_t s);

    public:
        lru_cache():
            bitree(10 * 1000 * 1000, 0),
            seqnums(1u << 24, 0),
            seq(1)     {}
        uint32_t access(uint32_t addr);
};

void lru_cache::update(uint32_t s, int16_t v)
{
    for (; s - 1 < bitree.size(); s += s & (-s))
        bitree[s - 1] += v;
}

uint32_t lru_cache::get_count(uint32_t s)
{
    uint32_t count = 0;
    for (; s > 0; s -= s & (-s))
        count += bitree[s - 1];
    return count;
}

uint32_t lru_cache::access(uint32_t addr)
{
    uint32_t count;
    if (seqnums[addr] == 0)
        count = numeric_limits<uint32_t>::max();
    else {
        count = get_count(seq) - get_count(seqnums[addr]);
        update(seqnums[addr], -1);
    }
    update(seqnums[addr] = seq++, 1);
    return count;
}

int main()
{
    lru_cache cache;

    uint16_t n;
    cin >> n;
    vector<uint32_t> sizes(n);
    for (auto &s: sizes)
        cin >> s;

    vector<uint32_t> misses(n, 0);
    for (char cmd[6]; cin >> cmd && cmd[0] != 'E'; ) {
        switch (cmd[0]) {
            case 'A': {
                uint32_t x;
                cin >> x;
                uint32_t count = cache.access(x);
                for (uint16_t i = 0; i < n && sizes[i] <= count; i++)
                    misses[i]++;
                break;
            }
            case 'R': {
                int32_t b, y, m;
                cin >> b >> y >> m;

                for (int32_t k = 0; k < m; k++) {
                    uint32_t count = cache.access(b + y * k);
                    for (uint16_t i = 0; i < n && sizes[i] <= count; i++)
                        misses[i]++;
                }
                break;
            }
            case 'S':
                for (uint16_t i = 0; i < n; i++) {
                    cout << (i == 0 ? "" : " ") << misses[i];
                    misses[i] = 0;
                }
                cout << endl;
        }
    }

    return 0;
}
