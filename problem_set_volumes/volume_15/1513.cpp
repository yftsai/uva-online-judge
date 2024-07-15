// #binary_tree
#include <iostream>
#include <vector>
using namespace std;

struct node
{
    bool is_used;
    uint32_t size;
};

uint32_t last(uint32_t n, uint32_t i = 0)
{
    while (i * 2 + 2 < n)
        i = i * 2 + 2;
    return i;
}

uint32_t prev(uint32_t n, uint32_t i)
{
    if (i * 2 + 1 < n)
        i = last(n, i * 2 + 1);
    else {
        while (i % 2 == 1)
            i = i / 2;
        i = i / 2 - 1;
    }
    return i;
}

void update(vector<node> &tree, uint32_t i)
{
    uint32_t left = i * 2 + 1;
    tree[i].size  = (left     < tree.size()) ? tree[left].size     : 0;
    tree[i].size += (left + 1 < tree.size()) ? tree[left + 1].size : 0;
    if (tree[i].is_used)
        tree[i].size++;
}

void prepend(vector<node> &tree, uint32_t head)
{
    tree[head].is_used = true;
    update(tree, head);
    while (head > 0)
        update(tree, head = (head - 1) / 2);
}

void remove(vector<node> &tree, uint32_t i)
{
    tree[i].is_used = false;
    update(tree, i);
    while (i > 0)
        update(tree, i = (i - 1) / 2);
}

uint32_t count_preds(const vector<node> &tree, uint32_t i)
{
    uint32_t left = i * 2 + 1;
    uint32_t count = (left < tree.size()) ? tree[left].size : 0;
    while (i != 0) {
        while (i % 2 == 1)
            i /= 2;
        if (i > 0) {
            count += tree[i - 1].size;
            if (tree[i / 2 - 1].is_used) count++;
            i = i / 2 - 1;
        }
    }
    return count;
}

int main()
{
    uint16_t ncases;
    uint32_t n, m;
    vector<node> tree;
    vector<uint32_t> indexes;
    for (cin >> ncases; ncases > 0 && cin >> n >> m; ncases--) {
        // use a complete binary tree to accommodate (n + m) elements
        tree.resize(n + m);
        indexes.resize(n + 1);
        uint32_t head = last(tree.size());
        for (auto &n: tree)
            n.is_used = false;
        for (uint32_t i = n; i > 0; i--) {
            tree[head].is_used = true;
            indexes[i] = head;
            head = prev(tree.size(), head);
        }
        for (uint32_t i = tree.size(); i > 0; i--)
            update(tree, i - 1);

        for (uint32_t i = 0, a; i < m && cin >> a; i++) {
            auto index = indexes[a];
            cout << (i > 0 ? " " : "") << count_preds(tree, index);
            remove(tree, index);
            prepend(tree, head);
            indexes[a] = head;
            head = prev(tree.size(), head);
        }
        cout << endl;
    }

    return 0;
}
