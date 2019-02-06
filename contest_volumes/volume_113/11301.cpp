// #minimum-cost_flow
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <limits>
using namespace std;

struct node
{
    map<node *, int> neighbors;
    node *parent;
    int cost;
};

struct node_ptr_comparer
{
    bool operator()(const node *m, const node *n) const
    {
        if (m->cost != n->cost)
            return m->cost < n->cost;
        else
            return m < n;
    }
};

int main()
{
    const int unreachable = numeric_limits<int>::max();
    string tolls[5];
    vector<node> ins[5], outs[5];
    node source, sink;
    source.cost = 0;
    for (uint16_t n = 0; cin >> n && n > 0; ) {
        for (string &t: tolls)
            cin >> t;

        source.neighbors.clear();
        sink.neighbors.clear();
        for (uint16_t i = 0; i < 5; ++i) {
            ins[i].resize(n);
            outs[i].resize(n);
            if (tolls[i][0] == '@')
                source.neighbors[ &ins[i][0] ] = 0;

            for (uint16_t j = 0; j < n; ++j) {
                ins[i][j].neighbors.clear();
                outs[i][j].neighbors.clear();

                ins[i][j].neighbors[ &outs[i][j] ] = (tolls[i][j] == '@') ? 0 : (tolls[i][j] - '0');
                if (i > 0 && tolls[i - 1u][j] != '@')
                    outs[i][j].neighbors[ &ins[i - 1u][j] ] = 0;
                if (i > 0 && tolls[i][j] != '@')
                    outs[i - 1u][j].neighbors[ &ins[i][j] ] = 0;
                if (j > 0 && tolls[i][j - 1u] != '@')
                    outs[i][j].neighbors[ &ins[i][j - 1u] ] = 0;
                if (j > 0 && tolls[i][j] != '@')
                    outs[i][j - 1u].neighbors[ &ins[i][j] ] = 0;
            }
            outs[i].back().neighbors[ &sink ] = 0;
        }

        int cost = 0;
        source.cost = 0;
        for (int y = 0; y < 5 && source.neighbors.size() > 0; ++y) {
            for (uint16_t i = 0; i < 5; ++i)
                for (uint16_t j = 0; j < n; ++j)
                    ins[i][j].cost = outs[i][j].cost = unreachable;
            sink.cost = unreachable;

            set<node *, node_ptr_comparer> pq;
            for (pq.insert(&source); pq.size() > 0; ) {
                node *m = *pq.begin();
                pq.erase(pq.begin());
                for (const auto &edge: m->neighbors) {
                    node *n = edge.first;
                    if (n->cost != unreachable && n->cost > m->cost + edge.second)
                        pq.erase(n);
                    if (n->cost == unreachable || n->cost > m->cost + edge.second) {
                        n->cost = m->cost + edge.second;
                        n->parent = m;
                        pq.insert(n);
                    }
                }
            }

            cost += sink.cost;
            for (node *n = &sink; n != &source; n = n->parent) {
                auto eit = n->parent->neighbors.find(n);
                n->neighbors[n->parent] = -eit->second;
                n->parent->neighbors.erase(eit);
            }
        }
        cout << cost << endl;
    }
    return 0;
}
