// #set_union
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main()
{
    uint32_t test_count, f;
    vector<uint32_t> set_ids;
    vector<uint32_t> set_sizes;
    string name;

    for (cin >> test_count; test_count > 0 && cin >> f; --test_count) {
        map<string, uint32_t> ids;
        set_ids.clear();
        set_sizes.clear();
        for (uint32_t i = 0; i < f; ++i) {
            uint32_t sids[2];
            for (uint32_t j = 0; j < 2 && cin >> name; ++j) {
                auto it = ids.lower_bound(name);
                if (it == ids.end() || it->first != name) {
                    it = ids.emplace_hint(it, name, set_ids.size());
                    set_ids.push_back(set_ids.size());
                    set_sizes.push_back(1u);
                }
                sids[j] = it->second;
                for (; set_ids[ sids[j] ] != sids[j]; sids[j] = set_ids[ sids[j] ])
                    ;
                for (uint32_t f = it->second, g; set_ids[f] != sids[j]; f = g) {
                    g = set_ids[f];
                    set_ids[f] = sids[j];
                }
            }

            if (sids[0] == sids[1])
                cout << set_sizes[ sids[0] ] << endl;
            else {
                set_ids[ sids[0] ] = sids[1];
                set_sizes[ sids[1] ] += set_sizes[ sids[0] ];
                cout << set_sizes[ sids[1] ] << endl;
            }
        }
    }

    return 0;
}
