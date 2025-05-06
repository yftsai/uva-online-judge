// #depth_first_search
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

pair<uint16_t, uint16_t> dfs(
    const vector<vector<uint16_t>> &network,
    uint16_t order, uint16_t p, uint16_t n,
    vector<uint16_t> &orders, vector<pair<uint16_t, uint16_t>> &wlinks)
{
    orders[n] = order;
    uint16_t low = order;
    order++;

    for (auto m: network[n])
        if (orders[m] == network.size()) {
            auto ret = dfs(network, order, n, m, orders, wlinks);
            order = ret.first;
            low = min(ret.second, low);
            if (orders[n] < ret.second)
                wlinks.emplace_back(min(n, m), max(n, m));
        }
        else if (m != p)
            low = min(orders[m], low);

    return pair<uint16_t, uint16_t>(order, low);
}

int main()
{
    vector<vector<uint16_t>> network;
    vector<uint16_t> orders;
    vector<pair<uint16_t, uint16_t>> wlinks;

    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        network.resize(n);
        for (auto &ms: network)
            ms.clear();

        for (uint16_t i = 0, ni, nj; i < m && cin >> ni >> nj; i++) {
            network[ni].push_back(nj);
            network[nj].push_back(ni);
        }

        orders.clear();
        orders.resize(n, n);
        wlinks.clear();
        dfs(network, 0, 0, 0, orders, wlinks);

        sort(wlinks.begin(), wlinks.end());
        cout << wlinks.size();
        for (auto &e: wlinks)
            cout << ' ' << e.first << ' ' << e.second;
        cout << endl;
    }

    return 0;
}
