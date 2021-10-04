// #dynamic_programming
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

constexpr uint16_t MAX_N = 16;
typedef bitset<MAX_N> tree_set;
typedef pair<int16_t, int16_t> location, evector;

int main()
{
    uint16_t case_count, n, m;
    vector<location> trees;
    vector<uint16_t> rays;
    vector<uint16_t> shot_counts;

    cin >> case_count;
    for (uint16_t case_no = 1; case_no <= case_count && cin >> n >> m; case_no++) {
        trees.resize(n);
        for (auto &t: trees)
            cin >> t.first >> t.second;

        rays.clear();
        for (uint16_t i = 0; i < n; i++)
            for (uint16_t j = i + 1; j < n; j++) {
                tree_set ts;
                ts.set(i);
                ts.set(j);

                auto create_evector = [](const location &from, const location &to) {
                    return evector(to.first  - from.first, to.second - from.second);
                };

                const auto vij = create_evector(trees[i], trees[j]);
                for (uint16_t k = j + 1; k < n; k++) {
                    const auto vik = create_evector(trees[i], trees[k]);
                    if (vij.first * vik.second == vij.second * vik.first)
                        ts.set(k);
                }

                rays.push_back(ts.to_ulong());
            }

        sort(rays.begin(), rays.end());
        rays.erase(unique(rays.begin(), rays.end()), rays.end());

        shot_counts.assign(1 << n, n);
        auto lower = [&shot_counts](const bitset<MAX_N> bs, uint16_t count) {
            const uint16_t index = bs.to_ulong();
            shot_counts[index] = min<uint16_t>(count, shot_counts[index]);
        };

        uint16_t min_shot_count = n;
        lower(bitset<MAX_N>(0), 0);
        for (uint32_t i = 0; i < shot_counts.size(); i++) {
            const tree_set ts(i);
            const auto count = shot_counts[i];

            if (ts.count() == m)
                min_shot_count = min(count, min_shot_count);
            else if (ts.count() < m) {
                // lower by a trivial shot
                for (uint16_t j = 0; j < n; j++)
                    if (!ts.test(j))
                        lower(tree_set(ts).set(j), count + 1);

                // lower by a directed shot
                for (const auto r: rays)
                    lower(ts | tree_set(r), count + 1);
            }
        }

        if (case_no > 1)
            cout << endl;
        cout << "Case #" << case_no << ":" << endl;
        cout << min_shot_count << endl;
    }

    return 0;
}
