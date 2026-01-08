// #binary_tree
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main()
{
    uint32_t k;
    uint16_t m, n;
    vector<int> adds;
    multiset<int> box;

    for (cin >> k; k > 0 && cin >> m >> n; k--) {
        adds.resize(m);
        for (auto &a: adds)
            cin >> a;

        box.clear();
        auto it = box.end();
        for (uint16_t i = 0, a = 0, g; i < n && cin >> g; i++, ++it) {
            while (box.size() < g) {
                auto v = adds[a++];
                box.insert(v);
                if (it == box.end() || v < *it)
                    --it;
            }

            cout << *it << endl;
        }

        if (k > 1)
            cout << endl;
    }

    return 0;
}
