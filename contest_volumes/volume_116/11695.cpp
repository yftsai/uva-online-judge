// #tree
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// returns (the height of the tree, the deepest leaf)
// traverse() also marks the parent of the visited node.
pair<uint16_t, uint16_t> traverse(const vector<set<uint16_t>> &tree,
                                  uint16_t p, uint16_t i,
                                  vector<uint16_t> &parents)
{
    parents[i] = p;

    pair<uint16_t, uint16_t> r(1, i);
    for (auto j: tree[i])
        if (parents[j] == tree.size()) {
            auto s = traverse(tree, i, j, parents);
            s.first++;
            r = max(s, r);
        }

    return r;
}

int main()
{
    vector<set<uint16_t>> tree;
    vector<uint16_t> parents;
    vector<uint16_t> diameter;
    vector<pair<uint16_t, uint16_t>> trees;     // (height, leaf)

    uint16_t tc, n;
    for (cin >> tc; tc > 0 && cin >> n; tc--) {
        tree.clear();
        tree.resize(n);
        for (uint16_t i = 1, a, b; i < n && cin >> a >> b; i++) {
            tree[a - 1].insert(b - 1);
            tree[b - 1].insert(a - 1);
        }

        parents.resize(n);
        fill(parents.begin(), parents.end(), n);
        uint16_t root = traverse(tree, 0, 0, parents).second;

        fill(parents.begin(), parents.end(), n);
        diameter.clear();
        diameter.push_back(traverse(tree, root, root, parents).second);
        while (parents[diameter.back()] != diameter.back())
            diameter.push_back(parents[diameter.back()]);

        // Consider splitting the tree into two:
        // "The front tree" from `diameter.front()` and "the back tree" from `diameter.back()`

        // A path from `diameter.front()` to "leaf" with length "len" is represented by a (len, leaf).
        // All `paths` are parts of the front tree, and the longest one is the diameter.
        set<pair<uint16_t, uint16_t>> paths;
        trees.clear();
        fill(parents.begin(), parents.end(), n);
        for (uint16_t i = 0; i < diameter.size(); i++) {
            if (i + 1u < diameter.size()) {
                tree[diameter[i]].erase(diameter[i + 1]);
                tree[diameter[i + 1]].erase(diameter[i]);
            }
            auto t = traverse(tree, diameter[i], diameter[i], parents);
            trees.emplace_back(t);
            paths.emplace(i + t.first - 1, t.second);
        }

        // The diameter of the back tree represented by (len, leaf)`
        // is a path from `diameter.back()` to "leaf" with length "len".
        pair<uint16_t, uint16_t> dback(0, root);
        uint16_t min_dlen = n;
        pair<uint16_t, uint16_t> cancel(root, root), add(root, root);

        for (uint16_t i = diameter.size() - 1; i > 0; i--) {
            // split the tree by removing the edge `diameter[i - 1]`-`diameter[i]`
            const auto p = trees[i];

            // shrink the front tree
            paths.erase(pair<uint16_t, uint16_t>(p.first + i - 1, p.second));
            auto dfront = *(--paths.end());
            // expand the back tree
            dback = max(pair<uint16_t, uint16_t>(p.first + diameter.size() - i - 2, p.second), dback);

            uint16_t dlen = max<uint16_t>(max(dfront.first, dback.first),
                                          (dfront.first + 1) / 2 + (dback.first + 1) / 2 + 1);
            if (dlen < min_dlen) {
                min_dlen = dlen;
                cancel = { diameter[i - 1], diameter[i]};
                add = { diameter[(dfront.first + 1) / 2] ,
                        diameter[diameter.size() - 1 - (dback.first + 1) / 2]};
            }
        }

        cout << min_dlen << endl;
        cout << (cancel.first + 1) << " " << (cancel.second + 1) << endl;
        cout << (add.first    + 1) << " " << (add.second    + 1) << endl;
    }

    return 0;
}
