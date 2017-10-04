// #maximum_flow #bipartite_matching
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

constexpr uint16_t source = 0, sink = 1;

bool augment(vector<set<uint16_t>> &edges)
{
    vector<uint16_t> parents(edges.size(), edges.size());
    queue<uint16_t> q;
    q.push(source);
    while (parents[sink] >= edges.size() && !q.empty()) {
        uint16_t n = q.front();
        q.pop();
        for (auto m: edges[n])
            if (parents[m] >= edges.size()) {
                parents[m] = n;
                q.push(m);
            }
    }

    if (parents[sink] >= edges.size())
        return false;
    else {
        for (uint16_t p = sink; p != source; p = parents[p]) {
            edges[p].insert(parents[p]);
            edges[ parents[p] ].erase(p);
        }
        return true;
    }
}

int main()
{
    int case_count;
    cin >> case_count;
    for (int case_number = 1; case_number <= case_count; case_number++) {
        uint16_t bolt_count, nut_count;
        cin >> bolt_count >> nut_count;
        vector<set<uint16_t>> edges(bolt_count + nut_count + 2);
        for (uint16_t b = 0; b < bolt_count; b++) {
            edges[source].insert(2 + b);
            for (uint16_t n = 0, is_fit; n < nut_count && cin >> is_fit; n++)
                if (is_fit != 0)
                    edges[2 + b].insert(2 + bolt_count + n);
        }
        for (uint16_t n = 0; n < nut_count; n++)
            edges[2 + bolt_count + n].insert(sink);

        while (augment(edges))
            ;
        cout << "Case " << case_number << ": a maximum of " << edges[sink].size() << " nuts and bolts can be fitted together" << endl;
    }
    return 0;
}
