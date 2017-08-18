// #maximum_flow
// Augmenting with BFS rather than DFS is faster in the judge likely due to depriorizing reassignments.
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node
{
    map<node*, int> capacities;
};

int augment(node *source, node *sink)
{
    map<node*, node*> from;
    queue<node*> q;
    from[source] = nullptr;
    q.push(source);
    for (; !q.empty() && from.find(sink) == from.end(); q.pop())
        for (auto &c: q.front()->capacities)
            if (from.find(c.first) == from.end()) {
                from[c.first] = q.front();
                q.push(c.first);
            }
    if (from.find(sink) == from.end())
        return 0;
    else {
        int flow = numeric_limits<int>::max();
        for (node *p = sink; p != source; p = from[p])
            flow = min(flow, from[p]->capacities[p]);
        for (node *p = sink; p != source; p = from[p]) {
            if (p->capacities.find(from[p]) == p->capacities.end())
                p->capacities[ from[p] ] = flow;
            else
                p->capacities[ from[p] ] += flow;

            if (from[p]->capacities[p] == flow)
                from[p]->capacities.erase(from[p]->capacities.find(p));
            else
                from[p]->capacities[p] -= flow;
        }
        return flow;
    }
}

int main()
{
    for (int case_count = 1, n, m; (cin >> n) && n != 0; case_count++) {
        cin >> m;

        int vs[n], as[n], bs[n];
        for (int i = 0; i < n && cin >> vs[i] >> as[i] >> bs[i]; i++)
            ;
        set<int> s(as, as + n);
        s.insert(bs, bs + n);
        const vector<int> times(s.begin(), s.end());

        node source, sink;
        node monkeys[n];
        node intervals[times.size() - 1];
        for (int i = 0; i < n; i++) {
            source.capacities[monkeys + i] = vs[i];
            for (auto it = lower_bound(times.begin(), times.end(), as[i]); it != lower_bound(times.begin(), times.end() - 1, bs[i]); it++)
                monkeys[i].capacities[ &intervals[it - times.begin()] ] = min(vs[i], *next(it) - *it);
        }
        for (size_t i = 0; i < times.size() - 1; i++)
            intervals[i].capacities[&sink] = m * (times[i+1] - times[i]);

        while (augment(&source, &sink) > 0)
            ;

        cout << "Case " << case_count << (source.capacities.size() > 0 ? ": No" : ": Yes") << endl;
        if (source.capacities.size() == 0)
        {
            vector<pair<int, int>> schedule[n];
            for (size_t i = 0; i < times.size() - 1; i++) {
                int duration = times[i+1] - times[i];
                int t = 0;
                for (auto &c: intervals[i].capacities)
                    if (c.first != &sink) {
                        auto add = [&](int a, int b) {
                            auto &s = schedule[c.first - monkeys];
                            if (s.size() == 0 || s.back().second != a)
                                s.push_back(pair<int, int>(a, b));
                            else
                                s.back().second = b;
                        };
                        if (c.second >= duration)
                            add(times[i], times[i+1]);
                        else if (t + c.second <= duration)
                            add(times[i] + t, times[i] + t + c.second);
                        else {
                            add(times[i], times[i] + (t + c.second) % duration);
                            add(times[i] + t, times[i+1]);
                        }
                        t = (t + c.second) % duration;
                    }
            }
            for (const auto &s: schedule) {
                cout << s.size();
                for (const auto &p: s)
                    cout << " (" << p.first << "," << p.second << ")";
                cout << endl;
            }
        }
    }

    return 0;
}
