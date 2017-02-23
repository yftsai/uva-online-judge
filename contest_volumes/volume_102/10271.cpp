// #dynamic_programming
// The key is to reduce the problem to find pairs when only the smaller chopsticks are considered.
// Finding pairs takes in O(n^2). Matching pairs into triplets also takes O(n^2).
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int t, k, n;

    for (cin >> t; t>0; --t) {
        cin >> k >> n;
        vector<int> lengths(n);
        for (auto &l: lengths)
            cin >> l;

        vector<map<pair<int, int>, int>> badnesses(3);
        badnesses[0][make_pair(0, 0)] = 0;
        for (int c=0; c<n; ++c) {
            for (auto &bs: badnesses[0]) {
                const int triplet_count = bs.first.first;
                const int pair_count = bs.first.second;

                // make the next two chopsticks a pair
                if (triplet_count + pair_count + 1 <= k+8) {
                    int b = bs.second + (lengths[c]-lengths[c+1])*(lengths[c]-lengths[c+1]);
                    auto p = badnesses[2].emplace(make_pair(triplet_count, pair_count+1), b);
                    if (!p.second) p.first->second = min(b, p.first->second);
                }

                // ignore the chopstick whenever possible
                if (c + pair_count + (k+8-triplet_count-pair_count)*3 < n) {
                    auto p = badnesses[1].emplace(make_pair(triplet_count, pair_count), bs.second);
                    if (!p.second) p.first->second = min(bs.second, p.first->second);
                }
                // match the chopstick with a pair
                // If pair_count == 0, the chopstick must be part of a pair. This case has been covered.
                else if (pair_count > 0) {
                    auto p = badnesses[1].emplace(make_pair(triplet_count+1, pair_count-1), bs.second);
                    if (!p.second) p.first->second = min(bs.second, p.first->second);
                }
            }
            swap(badnesses[0], badnesses[1]);
            swap(badnesses[1], badnesses[2]);
            badnesses[2].clear();
        }
        cout << badnesses[0].begin()->second << endl;
    }

    return 0;
}
