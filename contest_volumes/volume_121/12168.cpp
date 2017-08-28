#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

bool augment(vector<set<uint16_t>> &nodes)
{
    const uint16_t source(nodes.size() - 1), sink(nodes.size() - 2);
    const uint16_t unknown = numeric_limits<uint16_t>::max();
    queue<uint16_t> q;
    vector<uint16_t> ins(nodes.size(), unknown);

    q.push(source);
    ins[source] = source;
    while (!q.empty() && ins[sink] == unknown) {
        uint16_t n = q.front();
        q.pop();
        for (uint16_t m: nodes[n])
            if (ins[m] == unknown) {
                ins[m] = n;
                q.push(m);
            }
    }

    if (ins[sink] == unknown)
        return false;
    else {
        for (uint16_t p = sink; p != source; p = ins[p]) {
            nodes[p].insert(ins[p]);
            nodes[ins[p]].erase(p);
        }
        return true;
    }
}

int main()
{
    int case_count;
    uint16_t c, d, v;
    for (cin >> case_count; case_count > 0 && cin >> c >> d >> v; case_count--) {
        vector<set<uint16_t>> pet_voters(c + d);
        vector<bool> is_cat_lover(v);
        for (uint16_t i = 0; i < v; i++) {
            char stay_p, leave_p;
            int stay_no, leave_no;
            cin >> stay_p >> stay_no >> leave_p >> leave_no;
            if (stay_p == 'C') {
                is_cat_lover[i] = true;
                pet_voters[stay_no - 1].insert(i);
                pet_voters[c + leave_no - 1].insert(i);
            }
            else {
                is_cat_lover[i] = false;
                pet_voters[c + stay_no - 1].insert(i);
                pet_voters[leave_no - 1].insert(i);
            }
        }

        vector<set<uint16_t>> nodes(v + 2);
        const uint16_t source(nodes.size() - 1), sink(nodes.size() - 2);
        for (uint16_t i = 0; i < v; i++)
            if (is_cat_lover[i])
                nodes[source].insert(i);
            else
                nodes[i].insert(sink);
        for (auto &voters: pet_voters)
            for (auto i: voters)
                if (is_cat_lover[i])
                    for (auto j: voters)
                        if (!is_cat_lover[j])
                            nodes[i].insert(j);

        while (augment(nodes))
            ;

        cout << (v - nodes[sink].size()) << endl;
    }

    return 0;
}
