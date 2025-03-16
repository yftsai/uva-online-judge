// #binary_tree
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct node
{
    uint16_t left, right;
    int32_t value;
};

uint16_t transform(vector<node> &tree, uint16_t n)
{
    if (tree[n].left == n)
        tree[n].value = 0;
    else
        tree[n].value = transform(tree, tree[n].left);

    uint16_t rsize = (tree[n].right == n) ? 0 : transform(tree, tree[n].right);
    return tree[n].value + 1 + rsize;
}

void produce_tree_shape(const vector<node> &tree, uint16_t n, vector<int32_t> &shape)
{
    shape.push_back(tree[n].value);
    if (tree[n].left != n)
        produce_tree_shape(tree, tree[n].left, shape);
    if (tree[n].right != n)
        produce_tree_shape(tree, tree[n].right, shape);
}

int main()
{
    vector<vector<int32_t>> shapes;
    vector<node> tree;

    for (uint16_t n, k; cin >> n >> k; ) {
        shapes.resize(n);
        tree.resize(k);
        for (auto &s: shapes) {
            for (uint16_t i = 0; i < k; i++) {
                cin >> tree[i].value;
                tree[i].left = tree[i].right = i;
                for (uint16_t p = 0; p != i; )
                    if (tree[i].value < tree[p].value) {
                        if (tree[p].left == p)
                            tree[p].left = i;
                        p = tree[p].left;
                    }
                    else {
                        if (tree[p].right == p)
                            tree[p].right = i;
                        p = tree[p].right;
                    }
            }

            transform(tree, 0);
            s.clear();
            produce_tree_shape(tree, 0, s);
        }

        sort(shapes.begin(), shapes.end());
        auto it = unique(shapes.begin(), shapes.end());
        cout << (it - shapes.begin()) << endl;
    }

    return 0;
}
