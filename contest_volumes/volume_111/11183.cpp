// #minimum_spanning_arborescence
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

const int invalid_cost = numeric_limits<int>::max();
typedef map<uint16_t, pair<uint16_t, int>> graph;   // edge destination, edge source, cost
typedef map<uint16_t, map<uint16_t, int>> edges;

void add_edge(int dst, pair<uint16_t, int> src_c, graph &min_costs, edges &other_costs)
{
    if (min_costs.find(dst) != min_costs.end() && src_c.second < min_costs[dst].second)
        swap(min_costs[dst], src_c);

    if (dst == 0 || dst == src_c.first)
        ;
    else if (min_costs.find(dst) == min_costs.end())
        min_costs[dst] = src_c;
    else if (other_costs.find(dst) == other_costs.end()
        || other_costs[dst].find(src_c.first) == other_costs[dst].end()
        || src_c.second < other_costs[dst][src_c.first])
        other_costs[dst][src_c.first] = src_c.second;
}

set<uint16_t> get_cycle(const graph &min_costs, uint16_t p, set<uint16_t> &reachable)
{
    set<uint16_t> cycle;
    auto get_source = [&](int dst) { return min_costs.find(dst)->second.first; };
    bool is_reachable = false;
    for (uint32_t i = 0, q = p; i <= min_costs.size() && !(is_reachable = reachable.find(q) != reachable.end()); i++, q = get_source(q))
        ;
    if (is_reachable)
        for (int q = p; reachable.find(q) == reachable.end(); q = get_source(q))
            reachable.insert(q);
    else {
        for (int q = get_source(p); p != q; p = get_source(p), q = get_source(get_source(q)))
            ;
        for (; cycle.count(p) == 0; p = get_source(p))
            cycle.insert(p);
    }
    return cycle;
}

int get_min_cost(graph &min_costs, edges &other_costs)
{
    int cost = 0;
    for (set<uint16_t> reachable = {0}; reachable.size() < min_costs.size() + 1; ) {
        set<uint16_t> cycle;
        for (auto it = min_costs.begin(); it != min_costs.end() && cycle.size() == 0; it++)
            cycle = get_cycle(min_costs, it->first, reachable);

        if (cycle.size() > 0) {
            for (auto v: cycle)
                cost += min_costs[v].second;

            int c = min_costs.rbegin()->first + 1;
            graph update_min_costs;
            edges update_other_costs;
            auto is_in_cycle = [&](uint16_t v) { return cycle.find(v) != cycle.end(); };
            for (const auto dst_e: min_costs)
                if (!is_in_cycle(dst_e.first)) {
                    if (is_in_cycle(dst_e.second.first))
                        add_edge(dst_e.first, pair<int, int>(c, dst_e.second.second), update_min_costs, update_other_costs);
                    else
                        add_edge(dst_e.first, dst_e.second, update_min_costs, update_other_costs);
                }
            for (const auto &dst_es: other_costs)
                for (const auto &src_c: dst_es.second)
                    if (!is_in_cycle(dst_es.first))
                        if (is_in_cycle(src_c.first))
                            add_edge(dst_es.first, pair<int, int>(c, src_c.second), update_min_costs, update_other_costs);
                        else
                            add_edge(dst_es.first, src_c, update_min_costs, update_other_costs);
                    else if (!is_in_cycle(src_c.first))
                        add_edge(c, pair<int, int>(src_c.first, src_c.second - min_costs[dst_es.first].second), update_min_costs, update_other_costs);
            min_costs.swap(update_min_costs);
            other_costs.swap(update_other_costs);

            // it's impossible to reach c
            if (min_costs.find(c) == min_costs.end())
                return invalid_cost;
        }
    }
    for (auto &es: min_costs)
        cost += es.second.second;
    return cost;
}

int main()
{
    int case_count;
    cin >> case_count;
    for (int case_number = 1; case_number <= case_count; case_number++) {
        uint32_t n, m;
        cin >> n >> m;
        graph min_costs;
        edges other_costs;
        for (uint16_t i = 0, u, v, w; i < m && cin >> u >> v >> w; i++)
            add_edge(v, pair<int, int>(u, w), min_costs, other_costs);

        int cost = (min_costs.size() + 1 < n) ? invalid_cost : get_min_cost(min_costs, other_costs);
        if (cost == invalid_cost)
            cout << "Case #" << case_number << ": Possums!" << endl;
        else
            cout << "Case #" << case_number << ": " << cost << endl;
    }

    return 0;
}
