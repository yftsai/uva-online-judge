// #tree
#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
using namespace std;

class sequence
{
    private:
        vector<uint32_t> tree;      // a complete tree
                                    // The leaves stores the values.
                                    // The internal nodes stores the size of the subtree.
        uint32_t root, end, cap;

        static uint32_t parent(uint32_t pos)    { return (pos - 1) / 2; }
    public:
        sequence();
        uint32_t evict(uint32_t pos);       // returns the count of values after `pos`
        uint32_t push_back(uint32_t v);     // returns the position of the new value
};

sequence::sequence():
    root((1 << 23) - 1),
    end((1 << 24) - 1),
    cap((1 << 24) + 1)
{
    tree.resize(1 << 25);    // sufficient leaves for 10 ** 7 data references
    tree[root] = 0;
}

uint32_t sequence::evict(uint32_t pos)
{
    uint32_t count = (pos % 2 == 1) ? tree[parent(pos)] - 1 : 0;
    for (uint32_t p = parent(pos); p != root; p = parent(p))
        if (p % 2 == 1)
            count += tree[p + 1];

    do {
        pos = parent(pos);
        tree[pos] -= 1;
    } while (pos != root);

    return count;
}

uint32_t sequence::push_back(uint32_t v)
{
    // expand the capacity
    if (end == cap) {
        root = parent(root);
        tree[root] = tree[root * 2 + 1];
        for (uint32_t c = root; (c = c * 2 + 2) < tree.size(); )
            cap = c;
        cap++;
    }

    tree[end++] = v;
    uint32_t p = end - 1;
    do {
        p = parent(p);
        tree[p]++;
    } while (p != root);

    return end - 1;
}

int main()
{
    unordered_map<uint32_t, int32_t> entries;
    sequence order;

    auto access = [&](uint32_t a) -> uint32_t {
        auto result = entries.emplace(a, -1);

        uint32_t count = result.second ?
            numeric_limits<uint32_t>::max() :
            order.evict(result.first->second);

        result.first->second = order.push_back(a);
        return count;
    };

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
                uint32_t count = access(x);
                for (uint16_t i = 0; i < n; i++)
                    if (count >= sizes[i])
                        misses[i]++;
                break;
            }
            case 'R': {
                int32_t b, y, m;
                cin >> b >> y >> m;

                for (int32_t k = 0; k < m; k++) {
                    uint32_t count = access(b + y * k);
                    for (uint16_t i = 0; i < n; i++)
                        if (count >= sizes[i])
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
