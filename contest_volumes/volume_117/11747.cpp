// #minimum_spanning_tree #easy
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct edge
{
    uint16_t nodes[2];
    uint32_t weight;
    bool is_tree_edge;

    bool operator<(const edge &e) const
    {
        return weight < e.weight;
    }
};

int main()
{
    vector<uint16_t> tree_ids;
    auto get_tree_id = [&tree_ids](uint16_t n) {
        uint16_t t = n;
        for (; t != tree_ids[t]; t = tree_ids[t])
            ;
        for (uint16_t m; n != t; n = m) {
            m = tree_ids[n];
            tree_ids[n] = t;
        }
        return t;
    };
    vector<edge> edges;
    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        edges.resize(m);
        for (edge &e: edges) {
            cin >> e.nodes[0] >> e.nodes[1] >> e.weight;
            e.is_tree_edge = false;
        }
        sort(edges.begin(), edges.end());

        tree_ids.resize(n);
        iota(tree_ids.begin(), tree_ids.end(), 0);
        uint16_t tree_edge_count = 0;
        for (edge &e: edges)
            if (tree_edge_count + 1u >= n)
                break;
            else {
                uint16_t n = get_tree_id(e.nodes[0]);
                uint16_t m = get_tree_id(e.nodes[1]);
                if (n != m) {
                    e.is_tree_edge = true;
                    ++tree_edge_count;
                    tree_ids[n] = m;
                }
            }

        if (tree_edge_count >= edges.size())
            cout << "forest" << endl;
        else {
            bool is_first_edge = true;
            for (const edge &e: edges)
                if (!e.is_tree_edge) {
                    cout << (is_first_edge ? "" : " ") << e.weight;
                    is_first_edge = false;
                }
            cout << endl;
        }
    }
    return 0;
}
