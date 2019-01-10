// #depth_first_search #strongly_connected_component
#include <iostream>
#include <vector>
using namespace std;

void get_post_order(const vector<vector<int>> &edges, int n, vector<bool> *is_visited, vector<int> *vertex_order)
{
    (*is_visited)[n] = true;
    for (int m: edges[n])
        if (!(*is_visited)[m])
            get_post_order(edges, m, is_visited, vertex_order);
    vertex_order->push_back(n);
}

int get_scc_size(const vector<vector<int>> &ins, int scc, int v, vector<bool> *is_visited, vector<int> *to_scc)
{
    (*is_visited)[v] = true;
    (*to_scc)[v] = scc;
    int size = 1;
    for (int u: ins[v])
        if (!(*is_visited)[u])
            size += get_scc_size(ins, scc, u, is_visited, to_scc);
    return size;
}

struct scc
{
    int vertex;
    int size;
    int clique_size;
};

int get_max_reachable_clique_size(const vector<vector<int>> &outs, const vector<int> &to_scc, const vector<scc> &sccs, int u, vector<bool> *is_visited)
{
    (*is_visited)[u] = true;
    int size = 0;
    for (int v: outs[u])
        if (!(*is_visited)[v])
            size = max(size, get_max_reachable_clique_size(outs, to_scc, sccs, v, is_visited));
        else if (to_scc[u] != to_scc[v])
            size = max(size, sccs[ to_scc[v] ].clique_size);
    return size;
}

int main()
{
    vector<vector<int>> ins, outs;
    vector<int> vertex_order;
    vector<int> to_scc;
    vector<scc> sccs;
    vector<bool> is_visited;

    int test_count;
    for (cin >> test_count; test_count > 0; --test_count) {
        int n, m;
        cin >> n >> m;
        ins.assign(n, vector<int>());
        outs.assign(n, vector<int>());
        for (int i = 0, u, v; i < m && cin >> u >> v; ++i) {
            ins[v - 1].push_back(u - 1);
            outs[u - 1].push_back(v - 1);
        }

        vertex_order.clear();
        is_visited.assign(n, false);
        for (int u = 0; u < n; ++u)
            if (!is_visited[u])
                get_post_order(outs, u, &is_visited, &vertex_order);

        to_scc.resize(n);
        sccs.clear();
        is_visited.assign(n, false);
        for (auto it = vertex_order.rbegin(); it != vertex_order.rend(); ++it) {
            if (!is_visited[*it]) {
                int scc = int(sccs.size());
                sccs.emplace_back();
                sccs.back().vertex = *it;
                sccs.back().size = get_scc_size(ins, scc, *it, &is_visited, &to_scc);
            }
        }

        is_visited.assign(n, false);
        int max_clique_size = 0;
        for (auto it = sccs.rbegin(); it != sccs.rend(); ++it)
            if (!is_visited[it->vertex]) {
                int scc = to_scc[it->vertex];
                sccs[scc].clique_size = sccs[scc].size + get_max_reachable_clique_size(outs, to_scc, sccs, it->vertex, &is_visited);
                max_clique_size = max(max_clique_size, sccs[scc].clique_size);
            }
        cout << max_clique_size << endl;
    }

    return 0;
}
