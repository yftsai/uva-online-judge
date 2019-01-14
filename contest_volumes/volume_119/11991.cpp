// #easy
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main()
{
    for (uint32_t n, m; cin >> n >> m; ) {
        map<uint32_t, vector<uint32_t>> locations;
        for (uint32_t i = 0, v; i < n && cin >> v; ++i)
            locations[v].push_back(i + 1);

        for (uint32_t i = 0, k, v; i < m && cin >> k >> v; ++i) {
            auto it = locations.find(v);
            cout << ((it == locations.end() || k > it->second.size()) ? 0 : it->second[k - 1]) << endl;
        }
    }

    return 0;
}
