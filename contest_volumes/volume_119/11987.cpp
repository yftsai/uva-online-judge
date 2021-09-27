// #disjoint_set
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct node
{
    uint32_t parent;
    uint32_t count;
    uint32_t sum;       // valid only when the node is a root
};

uint32_t get_set(vector<node> &nodes, uint32_t i)
{
    uint32_t s = i;
    for (; nodes[s].parent != s; s = nodes[s].parent)
        ;

    uint32_t count = 0;
    for (uint32_t j = i, k; j != s; j = k) {
        k = nodes[j].parent;
        nodes[j].parent = s;

        count += nodes[j].count;
        nodes[k].count -= count;
    }
    nodes[s].count += count;

    return s;
}

int main()
{
    vector<uint32_t> indexes(1000 * 100 + 1);
    vector<node> nodes(1000 * 200);

    for (uint32_t n, m; cin >> n >> m; ) {
        indexes.resize(n + 1);  // indexes[0] is not used.
        iota(indexes.begin() + 1, indexes.end(), 0);

        nodes.resize(n);
        for (uint32_t i = 0; i < n; i++) {
            nodes[i].count = 1;
            nodes[i].sum = i + 1;
            nodes[i].parent = i;
        }

        char op;
        for (uint32_t i = 0, p, q; i < m && cin >> op >> p; i++) {
            auto pi = get_set(nodes, indexes[p]);

            if (op == '1') {
                cin >> q;
                const auto qi = get_set(nodes, indexes[q]);
                if (pi != qi) {
                    nodes[pi].parent = qi;
                    nodes[qi].count += nodes[pi].count;
                    nodes[qi].sum += nodes[pi].sum;
                }
            }
            else if (op == '2') {
                cin >> q;
                auto qi = get_set(nodes, indexes[q]);
                if (pi != qi) {
                    for (uint32_t j = indexes[p]; nodes[j].parent != pi; j = nodes[j].parent)
                        nodes[j].count--;
                    nodes[pi].count--;
                    nodes[pi].sum -= p;

                    // The implementation only reuses the immediate empty node for simplicity.
                    pi = indexes[p];
                    if (nodes[pi].count != 0) {
                        indexes[p] = pi = nodes.size();
                        nodes.emplace_back();
                    }
                    nodes[pi].count = 1;
                    nodes[pi].parent = qi;
                    nodes[qi].count++;
                    nodes[qi].sum += p;
                }
            }
            else
                cout << nodes[pi].count << " " << nodes[pi].sum << endl;
        }
    }

    return 0;
}
