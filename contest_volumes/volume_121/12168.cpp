#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
using namespace std;

struct node
{
    set<node*> outs;
};

bool augment(node *src, node *sink)
{
    queue<node*> q;
    map<node*, node*> ins;

    q.push(src);
    ins[src] = nullptr;
    while (!q.empty() && ins.find(sink) == ins.end()) {
        node *n = q.front();
        q.pop();
        for (node *m: n->outs)
            if (ins.find(m) == ins.end()) {
                ins[m] = n;
                q.push(m);
            }
    }

    if (ins.find(sink) == ins.end())
        return false;
    else {
        for (node *p = sink; p != src; p = ins[p]) {
            p->outs.insert(ins[p]);
            ins[p]->outs.erase(p);
        }
        return true;
    }
}

int main()
{
    int case_count, c, d, v;
    for (cin >> case_count; case_count > 0 && cin >> c >> d >> v; case_count--) {
        vector<set<int>> pet_voters(c + d);
        vector<bool> is_cat_lover(v);
        for (int i = 0; i < v; i++) {
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

        vector<node> nodes(v + 2);
        node &source = nodes[v], &sink = nodes[v+1];
        for (int i = 0; i < v; i++)
            if (is_cat_lover[i])
                source.outs.insert(&nodes[i]);
            else
                nodes[i].outs.insert(&sink);
        for (auto &voters: pet_voters)
            for (auto i: voters)
                if (is_cat_lover[i])
                    for (auto j: voters)
                        if (!is_cat_lover[j])
                            nodes[i].outs.insert(&nodes[j]);

        while (augment(&source, &sink))
            ;

        cout << (v - sink.outs.size()) << endl;
    }

    return 0;
}
