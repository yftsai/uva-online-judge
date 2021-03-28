// #priority_queue
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

typedef pair<uint16_t, vector<int>> heap;

static int get(heap &h, const uint16_t i)
{
    for (; i >= h.first; ++h.first)
        pop_heap(h.second.begin(), h.second.end() - h.first, greater<int32_t>());
    return *(h.second.end() - 1 - i);
}

struct state
{
    int sum;
    vector<uint16_t> indexes;
    vector<pair<int, uint16_t>> deltas;

    bool operator<(const state &s) const
    {
        return sum < s.sum;
    }
};

int main()
{
    vector<heap> heaps(750);
    vector<state> pq;

    for (uint16_t k; cin >> k; pq.clear()) {
        heaps.resize(k);
        for (auto &h: heaps) {
            h.first = 0;
            h.second.resize(k);
            for (auto &v: h.second)
                cin >> v;
            make_heap(h.second.begin(), h.second.end(), greater<int32_t>());
        }

        state s;
        s.sum = -accumulate(heaps.begin(), heaps.end(), 0,
                [](int32_t a, heap &h) { return a + get(h, 0); });
        s.indexes.assign(k, 0);
        s.deltas.reserve(k);
        for (uint16_t i = 0; i < k; ++i)
            s.deltas.emplace_back(get(heaps[i], 0) - get(heaps[i], 1), i);
        make_heap(s.deltas.begin(), s.deltas.end());

        cout << -s.sum;

        s.sum += s.deltas.begin()->first;
        pq.emplace_back(move(s));

        for (uint16_t i = 1; i < k; ++i) {
            pop_heap(pq.begin(), pq.end());
            s = move(pq.back());
            pq.pop_back();
            cout << " " << -s.sum;

            pop_heap(s.deltas.begin(), s.deltas.end());
            const int d = s.deltas.back().first;
            const uint16_t hi = s.deltas.back().second;
            s.deltas.pop_back();

            s.sum += -d + s.deltas[0].first;
            pq.push_back(s);
            make_heap(pq.begin(), pq.end());
            s.sum +=  d - s.deltas[0].first;

            const uint16_t j = s.indexes[hi];
            if (j + 2 < k) {
                s.deltas.emplace_back(get(heaps[hi], j + 1) - get(heaps[hi], j + 2), hi);
                push_heap(s.deltas.begin(), s.deltas.end());
                s.sum += s.deltas[0].first;
                s.indexes[hi]++;
                pq.emplace_back(move(s));
                push_heap(pq.begin(), pq.end());
            }
        }
        cout << endl;
    }

    return 0;
}
