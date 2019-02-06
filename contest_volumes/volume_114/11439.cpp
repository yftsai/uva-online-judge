// #blossom_algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void augment(const vector<vector<uint16_t>> &graph,
             const vector<uint16_t> &rpath,
             vector<uint16_t> &matches)
{
    for (uint16_t i = 0; i < rpath.size(); i += 2) {
        matches[ rpath[i] ] = rpath[i + 1];
        matches[ rpath[i + 1] ] = rpath[i];
    }
}

void find_augment_path(const vector<vector<uint16_t>> &graph,
                       const vector<uint16_t> &matches,
                       uint16_t start,
                       vector<uint16_t> &rpath)
{
    rpath.clear();
    const uint16_t node_count = graph.size(), invalid_node = graph.size();
    vector<uint16_t> parents(graph.size(), invalid_node);

    uint16_t end = invalid_node;
    for (vector<pair<uint16_t, uint16_t>> stack(1, pair<uint16_t, uint16_t>(start, 0)); stack.size() > 0 && end == invalid_node; ){
        const uint16_t m = stack.back().first;
        uint16_t i = stack.back().second;
        const auto &edges = graph[m];

        auto is_end = [&](uint16_t n) { return matches[n] == invalid_node || parents[ matches[n] ] != invalid_node; };
        auto is_next = [&](uint16_t n) { return parents[n] == invalid_node; };
        for (; i < edges.size(); ++i)
            if (is_end(edges[i]) || is_next(edges[i]))
                break;

        const uint16_t n = (i < edges.size()) ? edges[i] : invalid_node;
        if (i >= edges.size())
            stack.pop_back();
        else if (is_end(n))
            parents[ end = n ] = m;
        else {
            parents[n] = m;
            stack.back().second = i + 1u;
            stack.push_back(pair<uint16_t, uint16_t>(matches[n], 0));
        }
    }

    if (end == invalid_node)
        ;
    else if (end != start && matches[end] == invalid_node) {
        for (rpath.assign(1, end); parents[rpath.back()] != start; ) {
            rpath.push_back(parents[rpath.back()]);
            rpath.push_back(matches[rpath.back()]);
        }
        rpath.push_back(start);
    }
    else {
        uint16_t lca = end;
        vector<bool> blossom(node_count, false);
        for (uint16_t n = end, m; parents[n] != lca; n = matches[m]) {
            m = parents[n];
            parents[m] = n;
            blossom[m] = blossom[ matches[m] ] = true;
        }

        vector<vector<uint16_t>> g(graph.size());
        auto map = [&blossom, lca](uint16_t n) { return blossom[n] ? lca : n; };
        for (uint16_t n = 0; n < node_count; ++n) {
            auto &edges = g[map(n)];
            for (uint16_t m: graph[n])
                if (map(n) != map(m))
                    edges.push_back(map(m));
        }

        vector<uint16_t> rp;
        find_augment_path(g, matches, start, rp);
        for (uint16_t i = 0; i < rp.size(); ++i)
            if (rp[i] != lca)
                rpath.push_back(rp[i]);
            else {
                uint16_t n = rp[i - 1];
                auto it = find_if(graph[n].begin(), graph[n].end(), [&](uint16_t m) { return blossom[m]; });
                if (it != graph[n].end())
                    for (n = *it; n != lca; n = parents[ matches[n] ]) {
                        rpath.push_back(n);
                        rpath.push_back(matches[n]);
                    }
                rpath.push_back(lca);
            }
    }
}

struct edge
{
    uint8_t i, j;
    int icpc;
    bool operator<(const edge &e)   { return icpc < e.icpc; }
};

int main()
{
    vector<edge> edges;
    vector<int> icpcs;
    vector<uint16_t> partial_matches, matches, rpath;

    uint32_t case_count;
    cin >> case_count;
    for (uint32_t case_number = 1, n; case_number <= case_count && cin >> n; ++case_number, edges.clear()) {
        const uint16_t node_count = 1 << n;
        for (uint8_t i = 0; i < node_count; ++i)
            for (int j = i + 1, icpc; j < node_count && cin >> icpc; ++j)
                edges.push_back(edge {i, uint8_t(j), icpc});
        sort(edges.begin(), edges.end());

        icpcs.resize(edges.size());
        transform(edges.begin(), edges.end(), icpcs.begin(), [](const edge &e) { return e.icpc; });
        icpcs.erase(unique(icpcs.begin(), icpcs.end()), icpcs.end());

        const uint16_t invalid_node = node_count;
        auto edges_begin = edges.begin();
        size_t icpcs_begin = 0, icpcs_end = icpcs.size();
        partial_matches.assign(node_count, invalid_node);
        while (icpcs_begin + 1u < icpcs_end) {
            size_t icpcs_mid = (icpcs_begin + icpcs_end) / 2u;
            vector<vector<uint16_t>> graph(node_count);
            for (auto it = edges_begin; it != edges.end(); ++it)
                if (it->icpc >= icpcs[icpcs_mid]) {
                    graph[it->i].push_back(it->j);
                    graph[it->j].push_back(it->i);
                }
            uint16_t m;
            matches = partial_matches;
            for (m = 0; m < node_count; ++m)
                if (matches[m] == invalid_node) {
                    find_augment_path(graph, matches, m, rpath);
                    if (rpath.size() > 0)
                        augment(graph, rpath, matches);
                    else
                        break;
                }

            if (m == node_count) {
                icpcs_begin = icpcs_mid;
                edges_begin = lower_bound(edges_begin, edges.end(), edge { 0, 0, icpcs[icpcs_mid] });
            }
            else {
                icpcs_end = icpcs_mid;
                partial_matches.swap(matches);
            }
        }
        cout << "Case " << case_number << ": " << icpcs[icpcs_begin] << endl;
    }

    return 0;
}
