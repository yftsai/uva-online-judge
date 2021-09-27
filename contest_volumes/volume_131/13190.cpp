// #easy
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    pair<string, uint16_t> drugs[3000];     // name, interval
    vector<pair<uint32_t, uint16_t>> pq;    // time, index (priority)
    greater<pair<uint32_t, uint16_t>> cmp;

    uint16_t t, n, k;
    for (cin >> t; t > 0 && cin >> n >> k; t--) {
        pq.resize(n);
        for (uint16_t i = 0; i < n && cin >> drugs[i].first >> drugs[i].second; i++) {
            pq[i].first = drugs[i].second;
            pq[i].second = i;
        }

        make_heap(pq.begin(), pq.end(), cmp);
        for (uint16_t i = 0; i < k; i++) {
            pop_heap(pq.begin(), pq.end(), cmp);
            cout << pq.back().first << " " << drugs[pq.back().second].first << endl;

            pq.back().first += drugs[pq.back().second].second;
            push_heap(pq.begin(), pq.end(), cmp);
        }
    }

    return 0;
}
