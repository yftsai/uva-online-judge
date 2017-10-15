// #binary_tree
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    for (uint16_t n; cin >> n; ) {
        set<uint16_t> edges[n];
        vector<uint16_t> trees;
        for (uint16_t i = 0, k; i < n && cin >> k; i++) {
            if (k == 1)
                trees.push_back(i);
            for (uint16_t j; k > 0 && cin >> j; k--)
                edges[i].insert(j - 1);
        }

        vector<uint16_t> parents(n, n), heights(n, 1), children[n];
        for (vector<uint16_t> ts; trees.size() > 1; ts.swap(trees)) {
            ts.clear();
            for (uint16_t t: trees) {
                if (edges[t].size() == 1) {
                    uint16_t p = *edges[t].begin();
                    parents[t] = p;
                    children[p].push_back(t);
                    edges[t].erase(p);
                    edges[p].erase(t);
                    heights[p] = heights[t] + 1;
                    if (edges[p].size() == 1)
                        ts.push_back(p);
                }
            }
        }

        const uint16_t root = (trees.size() == 0) ? (find(parents.begin(), parents.end(), n) - parents.begin()) : trees[0];
        const uint16_t height = heights[root];
        vector<uint16_t> best_roots(1, root), worst_roots;
        copy_if(children[root].begin(), children[root].end(),
            back_inserter(worst_roots),
            [&](uint16_t n) { return heights[n] == height - 1; });
        if (worst_roots.size() == 1) {
            best_roots.push_back(worst_roots[0]);
            copy_if(children[root].begin(), children[root].end(),
                back_inserter(worst_roots),
                [&](uint16_t n) { return heights[n] == height - 2; });
        }
        for (uint16_t leaf_count = 0; leaf_count < worst_roots.size(); ) {
            uint16_t n = worst_roots[leaf_count];
            if (heights[n] == 1)
                leaf_count++;
            else {
                copy_if(children[n].begin(), children[n].end(),
                    back_inserter(worst_roots),
                    [&](uint16_t m) { return heights[m] == heights[n] - 1; });
                swap(worst_roots[leaf_count], worst_roots.back());
                worst_roots.pop_back();
            }
        }

        sort(best_roots.begin(), best_roots.end());
        cout << "Best Roots  :";
        for (uint16_t r: best_roots)
            cout << " " << (r + 1);
        cout << endl;
        sort(worst_roots.begin(), worst_roots.end());
        cout << "Worst Roots :";
        for (uint16_t r: worst_roots)
            cout << " " << (r + 1);
        cout << endl;
    }
    return 0;
}
