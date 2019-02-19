// #permutation
// A tree-based implementation is not required to solve this problem.
#include <iostream>
using namespace std;

struct node
{
    uint16_t number, size;
};

uint16_t tree_init(struct node *nodes, uint16_t length, uint16_t *value, uint32_t index = 0)
{
    if (index >= length)
        return 0;
    else {
        const uint32_t left = index * 2 + 1, right = index * 2 + 2;
        nodes[index].size = tree_init(nodes, length, value, left) + 1;
        nodes[index].number = (*value)++;
        nodes[index].size += tree_init(nodes, length, value, right);
        return nodes[index].size;
    }
}

uint16_t tree_remove(struct node *nodes, uint16_t length, uint16_t pos, uint32_t index = 0)
{
    const uint32_t left = index * 2 + 1, right = index * 2 + 2;
    nodes[index].size--;
    if (left >= length)
        return nodes[index].number;
    else if (pos < nodes[left].size)
        return tree_remove(nodes, length, pos, left);
    else if (right >= length || pos + nodes[right].size <= nodes[index].size)
        return nodes[index].number;
    else
        return tree_remove(nodes, length, pos + nodes[right].size - nodes[index].size - 1, right);
}

int main()
{
    struct node nodes[50000];
    uint16_t t, k, perm[50000]; // perm is introduced for performance.

    for (cin >> t; t > 0; t--) {
        cin >> k;
        uint16_t value = 1;
        tree_init(nodes, k, &value);

        for (uint16_t i = 1, s; i <= k && cin >> s; i++)
            perm[i - 1] = tree_remove(nodes, k, s);

        cout << perm[0];
        for (uint16_t i = 1; i < k; i++)
            cout << ' ' << perm[i];
        cout << endl;
    }
    return 0;
}
