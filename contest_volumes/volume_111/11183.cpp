// #minimum_spanning_arborescence
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef uint16_t node_id;
node_id invalid_id = numeric_limits<node_id>::max();

struct connections
{
    map<node_id, int> ins;  // set min_in to invalid after updating ins
    set<node_id> outs;
    node_id min_in;
};
typedef map<node_id, connections> graph;

void add_edge(node_id from, node_id to, int cost, graph &costs)
{
    if ((to != 0 && to != from)
        && (costs.find(to) == costs.end()
            || costs[to].ins.find(from) == costs[to].ins.end()
            || cost < costs[to].ins[from])) {
        costs[to].ins[from] = cost;
        costs[to].min_in = invalid_id;
        costs[from].outs.insert(to);
    }
}

void get_reachable(const graph &costs, node_id n, set<node_id> &reachable)
{
    graph::const_iterator it;
    if (reachable.find(n) != reachable.end() || (it = costs.find(n)) == costs.end())
        return;
    else {
        reachable.insert(n);
        for (const node_id &out: it->second.outs)
            get_reachable(costs, out, reachable);
    }
}

node_id get_min_in(connections &c)
{
    typedef pair<node_id, int> in_cost;
    auto compare_cost = [](const in_cost &ic1, const in_cost &ic2) { return ic1.second < ic2.second; };
    if (c.min_in == invalid_id)
        c.min_in = min_element(c.ins.begin(), c.ins.end(), compare_cost)->first;
    return c.min_in;
}

set<node_id> get_cycle(graph &costs, set<node_id> &reachable, node_id p)
{
    size_t remained_count = costs.size() - reachable.size();
    node_id q = p;
    for (size_t i = 0; i < remained_count && reachable.find(q) == reachable.end(); i++)
        q = get_min_in(costs[q]);
    set<node_id> cycle;
    if (reachable.find(q) != reachable.end())
        for (q = p; reachable.find(q) == reachable.end(); q = get_min_in(costs[q]))
            reachable.insert(q);
    else
        for (; cycle.find(q) == cycle.end(); q = get_min_in(costs[q]))
            cycle.insert(q);
    return cycle;
}

int get_min_cost(graph &costs)
{
    set<node_id> nodes;
    auto get_node_id = [](const pair<node_id, connections> &p) { return p.first; };
    transform(costs.begin(), costs.end(), inserter(nodes, nodes.end()), get_node_id);

    int cost = 0;
    set<node_id> reachable = {0};
    while (!nodes.empty()) {
        set<uint16_t> cycle = get_cycle(costs, reachable, *nodes.begin());
        if (cycle.size() == 0)
            nodes.erase(nodes.begin());
        else {
            node_id c = costs.rbegin()->first + 1;
            for (auto v: cycle) {
                int cost_in_cycle = costs[v].ins[ get_min_in(costs[v]) ];
                cost += cost_in_cycle;
                for (auto in_c: costs[v].ins)
                    if (cycle.find(in_c.first) == cycle.end()) {
                        add_edge(in_c.first, c, in_c.second - cost_in_cycle, costs);
                        costs[in_c.first].outs.erase(v);
                    }
                for (auto out: costs[v].outs)
                    if (cycle.find(out) == cycle.end()) {
                        add_edge(c, out, costs[out].ins[v], costs);
                        costs[out].ins.erase(v);
                        costs[out].min_in = invalid_id;
                    }
                costs.erase(costs.find(v));
                nodes.erase(v);
            }
            nodes.insert(c);
        }
    }
    reachable.erase(reachable.find(0));
    for (auto &v: reachable)
        cost += costs[v].ins[ get_min_in(costs[v]) ];
    return cost;
}

int main()
{
    int case_count;
    cin >> case_count;
    for (int case_number = 1; case_number <= case_count; case_number++) {
        uint16_t n, m;
        graph costs;
        cin >> n >> m;
        for (uint16_t i = 0, u, v, w; i < m && cin >> u >> v >> w; i++)
            add_edge(u, v, w, costs);

        set<node_id> reachable;
        get_reachable(costs, 0, reachable);
        if (reachable.size() < n)
            cout << "Case #" << case_number << ": Possums!" << endl;
        else
            cout << "Case #" << case_number << ": " << get_min_cost(costs) << endl;
    }

    return 0;
}
