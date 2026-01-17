// #breadth_first_search
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

constexpr uint8_t N = 9;

void cut_and_paste(const uint64_t seq, vector<uint64_t> &next)
{
    const uint64_t one = 1;
    next.clear();

    // cut [j, k) and paste at i where i < j
    for (uint8_t i = 0; i < N; i++) {
        uint8_t shift = 4 * (N - i);
        uint64_t seq_i = (seq >> shift) << shift;

        for (uint8_t k = i + 2; k <= N; k++) {
            shift = 4 * (N - k);
            uint64_t seq_k = seq & ((one << shift) - 1);

            for (uint8_t j = i + 1; j < k; j++) {
                shift = 4 * (N - k);
                uint64_t t = seq >> shift;
                shift = 4 * (k - j);
                uint64_t s = t & ((one << shift) - 1);
                t >>= shift;
                shift = 4 * (j - i);
                t = t & ((one << shift) - 1);
                t = (s << shift) | t;
                shift = 4 * (N - k);
                t <<= shift;

                next.push_back(seq_i | t | seq_k);
            }
        }
    }
}

int main()
{
    unordered_map<uint64_t, uint8_t> ops(56917);
    queue<pair<uint64_t, uint16_t>> q;

    uint64_t seq = 0;
    for (uint8_t i = 1; i <= N; i++)
        seq = (seq << 4) | i;
    ops.emplace(seq, 0);
    q.emplace(seq, 0);

    // Trick: All orders can be fixed within 5 operations.
    //        Cache orders requiring 3- operations.
    vector<uint64_t> next;
    while (!q.empty()) {
        seq = q.front().first;
        uint8_t o = q.front().second;
        q.pop();

        cut_and_paste(seq, next);
        for (auto t: next)
            if (ops.emplace(t, o + 1).second && o + 1 < 3)
                q.emplace(t, o + 1);
    }

    for (uint16_t case_no = 1, n; cin >> n && n > 0; case_no++) {
        seq = 0;
        for (uint16_t i = 0, p; i < n && cin >> p; i++)
            seq = (seq << 4) | p;

        // extends the given sequence
        for (uint16_t i = n + 1; i <= N; i++)
            seq = (seq << 4) | i;

        cout << "Case " << case_no << ": ";
        auto it = ops.find(seq);
        if (it != ops.end())
            cout << (uint16_t)it->second << endl;
        else {
            cut_and_paste(seq, next);
            if (any_of(next.begin(), next.end(), [&](uint64_t e) { return ops.find(e) != ops.end(); }))
                cout << 4 << endl;
            else
                cout << 5 << endl;
        }
    }

    return 0;
}
