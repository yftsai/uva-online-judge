#include <iostream>
#include <map>
using namespace std;

int main()
{
    uint32_t test_count, n;
    for (cin >> test_count; test_count > 0 && cin >> n; --test_count) {
        map<uint32_t, uint32_t> indexes;
        uint32_t i = 0, size = 0;
        for (uint32_t j = 0, id; j < n && cin >> id; ++j) {
            auto it = indexes.lower_bound(id);
            if (it == indexes.end() || it->first != id)
                indexes.emplace_hint(it, id, j);
            else {
                size = max(size, j - i);
                i = max(i, it->second + 1u);
                it->second = j;
            }
        }
        cout << max(size, n - i) << endl;
    }

    return 0;
}
