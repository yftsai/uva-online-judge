#include <iostream>
#include <vector>
using namespace std;

struct node {
    int rep, parent;
    int size;
    uint64_t length;
    int largest_child;
    uint16_t level;
};

int main()
{
    vector<node> nodes(100u * 1000u);
    nodes[0].rep = 0;
    nodes[0].level = 0;
    nodes[0].length = 0;

    for (int n; cin >> n && n != 0; ) {
        nodes.resize(n);
        nodes[0].size = 1;
        for (int i = 1; i < n && cin >> nodes[i].parent >> nodes[i].length; ++i) {
            nodes[i].rep = i;
            nodes[i].size = 1;
            nodes[i].largest_child = i;
            nodes[i].length += nodes[ nodes[i].parent ].length;
        }

        for (int i = n; i > 1; --i) {
            int p = nodes[i - 1].parent;
            nodes[p].size += nodes[i - 1].size;
            if (nodes[p].largest_child == p
                || nodes[ nodes[p].largest_child ].size < nodes[i - 1].size)
                nodes[p].largest_child = i - 1;
        }

        for (int i = 0; i < n; ++i) {
            int r = nodes[i].rep;
            nodes[i].level = (r == 0) ? 0 : nodes[ nodes[r].parent ].level + 1u;
            nodes[ nodes[i].largest_child ].rep = nodes[i].rep;
        }

        int q, s, t;
        for (cin >> q; q > 0 && cin >> s >> t; --q) {
            uint64_t length = nodes[s].length + nodes[t].length;

            for (; nodes[s].level > nodes[t].level; s = nodes[ nodes[s].rep ].parent)
                ;
            for (; nodes[s].level < nodes[t].level; t = nodes[ nodes[t].rep ].parent)
                ;
            for (; nodes[s].rep != nodes[t].rep; s = nodes[ nodes[s].rep ].parent, t = nodes[ nodes[t].rep ].parent)
                ;

            if (s == nodes[s].rep)
                length -= nodes[s].length * 2u;
            else if (t == nodes[t].rep)
                length -= nodes[t].length * 2u;
            else
                length -= min(nodes[s].length, nodes[t].length) * 2u;

            cout << length << ((q == 1) ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}
